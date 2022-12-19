// Written/edited in 12/22 by github.com/jakobkilian for the github.com/KISDinteractive/embedded_ai_22w course.

// This arduino code heavily inspired by a two-part video tutorial by Shawn Hymel
// - part 1: https://www.youtube.com/watch?v=BzzqYNYOcWc
// - part 2 https://www.youtube.com/watch?v=dU01M61RW8s
// This, however, is based on an example from arguably the most important book in TinyML: 
// https://www.oreilly.com/library/view/tinyml/9781492052036/)


// ----- INCLUDES ------
//Include libraries
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <M5StickCPlus.h>
//sine_model.h contains the NN array that we trained with Jupyter and TensorFlow
#include "sine_model.h"

// ----- TF STUFF ------
//Define inputs and outputs of model (one int in -> x, one int out -> corresponding y)
#define N_INPUTS 1
#define N_OUTPUTS 1
// Tensor Arena Size: Size needs to be found with trial and error.
#define TENSOR_ARENA_SIZE 5 * 1024
//Defining die actual model "tf"
using namespace Eloquent::TinyML::TensorFlow;
Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;

// ---- VARIABLES -----
//some variables for printign stuff to the screen
int screenWidth = 240;   //width of the m5stick screen
int screenHeight = 135;  //height of the m5stick screen
float initNo[240];       //the initial number that we want to work with
float sineNo[240];       //the actual sind val of initNo (calculated by using sine())
float predictedNo[240];  //the sine prediction by our model
int waveSize = 35;       //how much should the sine wave be scaled for displaying?
int offset = 0;          //to make it more appealing, we let the sine wave run from right to left. This value is used to move the wave


// ------ SETUP -------
void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);  //flip the screen
  tf.begin(sine_model);

  //Check if the model can be loaded without problems
  if (!tf.isOk()) {
    M5.Lcd.setCursor(10, 3);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("ERROR:");
    M5.Lcd.print("tf.getErrorMessage()");
    switch (tf.getError()) {
      case TensorFlowError::VERSION_MISMATCH:
        // Python version differs from C++ version
        break;
      case TensorFlowError::CANNOT_ALLOCATE_TENSORS:
        // either ARENA size is not enough to allocate the operations
        // or, if you used MutableTensorFlow, you didn't add all the
        // required operations
        break;
    }
    while (true) delay(1000);
  }
  M5.Lcd.setTextSize(1);
}

// ------ LOOP --------
void loop() {
  offset = offset + 3;  //move everything to the left by 3 pixels per frame
  calcAndPredict();     //do calculations and inference / prediction
  drawTextLabels();     //draw explanatory text labels
  drawSineWaves();      //draw the actual sine waves
}

// ----- FUNCTIONS -----
void calcAndPredict() {
  for (int i = 0; i <= screenWidth; i++) {
    initNo[i] = (2 * 3.14 * ((i + offset) % screenWidth)) / screenWidth;  //generate a inital number for every x-pixel between 0 and 2pi
    sineNo[i] = sin(initNo[i]);                                           //calc the real sine value of that number
    float input[1] = { initNo[i] };                                       //generate an array with only one value (that is what the model wishes)
    predictedNo[i] = tf.predict(input);                                   //generate the prediction of the neural network for the initial number
  }
}

void drawTextLabels() {
  M5.Lcd.setCursor(10, screenHeight - 20);
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.println("AI-Predicted Sine Wave");
  M5.Lcd.setCursor(10, 3);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.println("Calculated Sine Wave");
}

void drawSineWaves() {
  int screenVertCenter = screenHeight / 2;
  for (int i = 0; i <= (sizeof(sineNo) / sizeof(sineNo[0])); i++) {                         //Iterate through sineNo array
    M5.Lcd.drawLine(i, 25, i, screenHeight - 25, TFT_BLACK);                                //Overpaint last visual by painting a line from top to bottom without deleting the text lables
    M5.Lcd.drawPixel(i, int(sineNo[i] * waveSize) + screenVertCenter - 6, TFT_WHITE);       //Paint the CALUCALATED sine wave pixel by pixel in white with a 5 pixels offset to the middle
    M5.Lcd.drawPixel(i, int(predictedNo[i] * waveSize) + screenVertCenter + 6, TFT_GREEN);  //Paint the PREDICTED sine wave pixel by pixel in white with a 5 pixels offset to the middle
  }
}