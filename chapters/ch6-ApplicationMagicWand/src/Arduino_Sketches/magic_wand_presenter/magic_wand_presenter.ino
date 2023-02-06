/*
  Author: https://github.com/jakobkilian
  Date: 25-01-2023

  Content:
  This Arduino sketch is part of the Interactive Systems course at KISD in WS 22/23 (https://github.com/KISDinteractive/embedded_ai_22w)
  It is mainly based on a Github repo by "billiyz" (https://github.com/billiyz/tinyml-on-the-edge)
  but  has been optimized/ported to be used on an M5StickC-Plus (ESP32) MCU programmed with the Arduino IDE
  and the EloquentTinyML Library for Arduino by Simone Salerno (https://eloquentarduino.com/eloquent-tinyml/).

  Usage:
  1. use record_imu_data.ino sketch to record data
  2. use TFGyroData.ipynb to train a tflite model and export the model.h file
  3. use THIS sketch (including the just created model.h file) to run the inference on the M5Stick
*/

// _____ LIBRARIES _____
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <M5StickCPlus.h>
#include <Arduino.h>
#include <BleKeyboard.h>
#include "model.h"

// _____ SETTINGS _____
const float accelerationThreshold = 3;  // threshold of significance in G's
const int numSamples = 80;             // total amount of samples for one gesture
const int msBetweenSamples = 7;         // time between each of the samples
const int msAfterInference = 200;     // time to wait after inference is finished and new inference can start
unsigned int updateInterval = 500; // in ms


// _____ STORAGE FOR DATA _____
float aX = 0.0F;
float aY = 0.0F;
float aZ = 0.0F;
float gX = 0.0F;
float gY = 0.0F;
float gZ = 0.0F;
int counter = 0;
int samplesRead = numSamples;

// _____ ELOQUENT LIBRARY – INIT TENSORFLOW  _____
#define N_INPUTS 1536
#define N_OUTPUTS 1
#define TENSOR_ARENA_SIZE 10 * 1024 // Tensor Arena Size: Size needs to be found with trial and error.
using namespace Eloquent::TinyML::TensorFlow;
Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf; //Defining die actual model "tf"

// _____ BLUETOOTH KEYBOARD _____
BleKeyboard bleKeyboard("Magic Wand"); // name of the device
bool blestate = false;
bool lastBlestate = !blestate;
long myTimer;

// _____ SETUP _____
void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.begin();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
  bleKeyboard.begin();
  tf.begin(model);

  // check if model loaded fine
  if (!tf.isOk()) {
    while (true) delay(1000);
  }
}

// _____ LOOP _____
void loop() {
  float tensInput[numSamples * 6]; //create a float array to store recorded samples and provide it to tensorflow

  // wait for significant motion
  while (samplesRead == numSamples) {
    M5.update(); // update M5, get button values etc

    // run this every "updateInterval" ms... (e.g. 1000 -> 1s)
    if (millis() - myTimer >= updateInterval) {
      myTimer = millis();

      M5.Lcd.fillRect(0, 60, 135, 93, BLACK);  // fill middle  part of screen (do not override ble state icon)
      // only update display if there is a change in "blestate"
      if (lastBlestate != blestate) {
        if (blestate) {
          M5.Lcd.fillRect(0, 0, 135, 60, BLACK);  // fill upper part of screen
          M5.Lcd.setTextSize(1);
          M5.Lcd.setCursor(10, 10);
          M5.Lcd.print("Bluetooth Connected");
        }
        else {
          M5.Lcd.fillRect(0, 0, 135, 60, BLACK);  // fill upper part of screen
        }
        // store values to check if they change in the next iteration
        lastBlestate = blestate;
      }

      if (bleKeyboard.isConnected()) {  // if connected
        if (!blestate) {                // but state is not yet updated
          blestate = true;              // adapt ble state
        }
      }
      else {                            // if not connected:
        if (blestate) {                 // but state is not yet updated
          blestate = false;             // adapt ble state
        }
        else {
          M5.Lcd.fillRect(0, 0, 135, 60, BLACK);  // fill upper part of screen
          M5.Lcd.setCursor(10, 10);
          M5.Lcd.setTextSize(1);
          M5.Lcd.println("Searching ..."); // print msg
        }
      }
    }

    // get acceleration data to check, if there is a significant movement
    M5.IMU.getAccelData(&aX, &aY, &aZ);
    // sum up the absolutes
    float aSum = fabs(aX) + fabs(aY) + fabs(aZ);
    // check if it's above the threshold
    if (aSum >= accelerationThreshold) {
      // reset samplesRead and break while loop -> start recording samples
      samplesRead = 0;
      break;
    }
  }

  // RECORDING!
  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {
    long lastTime;
    // only record samples every 5 ms
    if (millis() - lastTime >= msBetweenSamples) {
      lastTime = millis();
      // read the acceleration and gyroscope data
      M5.IMU.getGyroData(&gX, &gY, &gZ);
      M5.IMU.getAccelData(&aX, &aY, &aZ);

      // normalize the IMU data between 0 to 1 and store in float array to be used as tf input
      tensInput[samplesRead * 6 + 0] = (aX + 8.0) / 16.0;
      tensInput[samplesRead * 6 + 1] = (aY + 8.0) / 16.0;
      tensInput[samplesRead * 6 + 2] = (aZ + 8.0) / 16.0;
      tensInput[samplesRead * 6 + 3] = (gX + 2000.0) / 4000.0;
      tensInput[samplesRead * 6 + 4] = (gY + 2000.0) / 4000.0;
      tensInput[samplesRead * 6 + 5] = (gZ + 2000.0) / 4000.0;

      // increment samplesRead to count every sample (until numSamples e.g. 80)
      samplesRead++;

      // when all samples are read and stored:
      if (samplesRead == numSamples) {

        // Run inference!
        long beginTime = millis(); // store time at beginning of inference
        // --------------------------------------------------------------------------------
        float predicted = tf.predict(tensInput); // HERE THE ACTUAL INFERENCE TAKES PLACE!
        // --------------------------------------------------------------------------------
        long elapsed = millis() - beginTime; // store elapsed time


        float predictionThresh = 0.1;
        // check if result is lower than 10% or higher than 90%.
        if (predicted >= predictionThresh && predicted <= 1.0 - predictionThresh) { // IF NOT
          M5.Lcd.fillRect(0, 60, 135, 93, TFT_DARKGREY);
          M5.Lcd.setTextSize(2);
          M5.Lcd.setCursor(20, 105);
          M5.Lcd.printf("not sure!");
        } else {
          if (blestate) {
            M5.Lcd.setTextSize(13);
            M5.Lcd.fillRect(0, 60, 135, 93, TFT_DARKGREEN);  // fill middle part of screen (do not override ble state icon)
            if (predicted < predictionThresh) { //IF BELOW 10%
              bleKeyboard.press(KEY_RIGHT_ARROW);   // press...
              bleKeyboard.release(KEY_RIGHT_ARROW); // and release right arrow key
              M5.Beep.tone(300, 300);
              M5.Lcd.setCursor(35, 80);
              M5.Lcd.printf("->");
            } else if (predicted > 1.0 * predictionThresh ) { //IF ABOVE 90%
              bleKeyboard.press(KEY_LEFT_ARROW);    // press...
              bleKeyboard.release(KEY_LEFT_ARROW);  // and release left arrow key
              M5.Beep.tone(500, 300);
              M5.Lcd.setCursor(20, 80);
              M5.Lcd.printf("<-");
            }
          }
        }
        // print inference time and percentage to screen
        M5.Lcd.fillRect(0, 60+93, 135, 100, TFT_DARKGREY);  // fill lower part of screen
        predicted = fabs(predicted - 1.0);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(10, 215);
        M5.Lcd.print(String(elapsed) + "ms");
        M5.Lcd.setCursor(90, 215);
        M5.Lcd.print(String(int(predicted * 100)) + "%");

        // draw visual bar for prediction percentage
        int barY = 170;
        int barX = 10;
        int barHeight = 20;
        int barWidth = 135 - 2 * barX;
        M5.Lcd.fillRect(barX, barY, barWidth, barHeight, TFT_LIGHTGREY ); // background of bar
        M5.Lcd.fillRect(barX, barY, barWidth * predictionThresh, barHeight, TFT_DARKGREEN); // mark lower threshold
        M5.Lcd.fillRect(1 + barX + barWidth - barWidth * predictionThresh, barY, barWidth * predictionThresh, barHeight, TFT_DARKGREEN); // mark upper threshold
        //M5.Lcd.drawRect(barX, barY, barWidth, barHeight, BLACK ); // border of bar
        M5.Lcd.fillRect(barX + predicted * barWidth, barY - 5, 2, barHeight + 10, BLACK); // plot prediction percentage as line
      }
    }
  }
  M5.Beep.mute();
  delay(msAfterInference);  // after one recording and inference: wait for some ms in order to not trigger the next right away
  myTimer = millis();       // reset update timer so that the display stays for some time
}
