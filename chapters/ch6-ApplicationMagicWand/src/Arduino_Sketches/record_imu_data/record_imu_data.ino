/*
  Author: https://github.com/jakobkilian
  Date: 25-01-2023

  Content:
  This Arduino sketch is part of the Interactive Systems course at KISD in WS 22/23 (https://github.com/KISDinteractive/embedded_ai_22w)
  It is mainly based on a Github repo by "billiyz" (https://github.com/billiyz/tinyml-on-the-edge)
  but  has been optimized/ported to be used on an M5StickC-Plus (ESP32) MCU programmed with the Arduino IDE
  and the EloquentTinyML Library for Arduino by Simone Salerno (https://eloquentarduino.com/eloquent-tinyml/).

  Usage:
  1. use THIS record_imu_data.ino sketch to record data
  2. use TFGyroData.ipynb to train a tflite model and export the model.h file
  3. use t he magic_wand_presenter sketch (including the just created model.h file) to run the inference on the M5Stick
*/


// _____ LIBRARIES _____
#include <M5StickCPlus.h>

// _____ SETTINGS _____
const float accelerationThreshold = 3;  // threshold of significant in G's
const int numSamples = 80;
const int msBetweenSamples = 5;         // time between each of the samples
const int msAfterRecord = 1500;     // time to wait after inference is finished and new inference can start


// _____ STORAGE FOR DATA _____
float aX = 0.0F;
float aY = 0.0F;
float aZ = 0.0F;
float gX = 0.0F;
float gY = 0.0F;
float gZ = 0.0F;
int counter = 0;
int samplesRead = numSamples;

// _____ SETUP _____
void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);

  M5.Imu.Init(); // start IMU
  Serial.begin(115200);
  delay(100);
  Serial.println("starting");
  Serial.println("aX,aY,aZ,gX,gY,gZ");   // print the header of the csv data
}

// _____ LOOP _____
void loop() {
  //Display "READY" Mode
  M5.Lcd.fillScreen(TFT_DARKGREEN);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("READY");
  M5.Lcd.setCursor(10, 100);
  M5.Lcd.print("No. " + String(counter));

  // wait for significant motion
  while (samplesRead == numSamples) {
    M5.update();                  // get changes from M5 libs
    if (M5.BtnA.wasPressed()) {
      ESP.restart();              // reset M5 (and counter) if button A gets pressed
    }
    M5.IMU.getAccelData(&aX, &aY, &aZ);           // get and save data from IMU
    float aSum = fabs(aX) + fabs(aY) + fabs(aZ);  // sum up the absolutes for detecting motion

    // check if acc sum is above the threshold
    if (aSum >= accelerationThreshold) {
      samplesRead = 0;    // reset the sample read count to trigger recording
      break;              // break while loop (go on with next task in "void loop")
    }
  }

  //Display "Recording" Mode
  M5.Lcd.fillScreen(ORANGE);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Recording");

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  long beginTime = millis();
  while (samplesRead < numSamples) {
    long lastTime;
    // only read data every msBetweenSamples to match the frequency of the interference
    if (millis() - lastTime >= msBetweenSamples) {
      lastTime = millis();

      // read the acceleration and gyroscope data
      M5.IMU.getGyroData(&gX, &gY, &gZ);
      M5.IMU.getAccelData(&aX, &aY, &aZ);
      samplesRead++;

      // print the data in CSV format to the Serial bus
      // use normalized data (between 0 and 1)
      Serial.print((aX + 8.0) / 16.0, 2);
      Serial.print(',');
      Serial.print((aY + 8.0) / 16.0, 2);
      Serial.print(',');
      Serial.print((aZ + 8.0) / 16.0, 2);
      Serial.print(',');
      Serial.print((gX + 2000.0) / 4000.0, 2);
      Serial.print(',');
      Serial.print((gY + 2000.0) / 4000.0, 2);
      Serial.print(',');
      Serial.print((gZ + 2000.0) / 4000.0, 2);
      Serial.println();

      // check if there are enough samples yet
      if (samplesRead == numSamples) {
        // add an empty line if it's the last sample
        Serial.println();
      }
    }
  }

  // Wait for 1s and display "Wait!" Screen
  // In this time one can move back to the starting position without triggering a new record....
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Wait!");
  delay(msAfterRecord);

  // increment the counter that gets displayed in the "READY" screen
  counter++;
}
