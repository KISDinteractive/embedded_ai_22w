//Include libraries
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>
#include <M5StickCPlus.h>

//sine_model.h contains the NN array
#include "sine_model.h"

//Define inputs and outputs of model
#define N_INPUTS 1
#define N_OUTPUTS 1
// Tensor Arena Size: Size needs to be found with trial and error.
#define TENSOR_ARENA_SIZE 5 * 1024

//Defining die actual model "tf"
using namespace Eloquent::TinyML::TensorFlow;
Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;


int screenW = 240;      //width of the m5stick screen
int screenH = 135;      //height of the m5stick screen
float initNo[240];      //the initial number that we want to work with
float sineNo[240];      //the actual sind val of initNo (calculated by using sine())
float predictedNo[240]; //the sine prediction by our model
int waveSize = 35;      //how much should the sine wave be scaled for displaying?

int offset = 0;             //to make it more appealing, we let the sine wave run from right to left. This value is used to move the wave

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3); //flip the screen
  tf.begin(sine_model);
  Serial.begin(115200);

  //Check if the model can be loaded without problems
  if (!tf.isOk()) {
    Serial.print("ERROR: ");
    Serial.println(tf.getErrorMessage());
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
  } else {
    Serial.println("The model loaded just fine, let's start...");
  }
}

void loop() {
  offset = offset+3; //move everything to the left by 3 pixels
  M5.Lcd.setCursor(0, 0, 2);

// Calculate and Predict
  for (int i = 0; i <= screenW; i++) {
    initNo[i] =  (2* 3.14 * ((i + offset) % screenW)) / screenW;  //generate a inital number for every x-pixel between 0 and 2pi
    sineNo[i] = sin(initNo[i]);                                   //calc the real sine value of that number
    float input[1] = { initNo[i] };                               //generate an array with only one value (that is what the model wishes)
    predictedNo[i] = tf.predict(input);                           //generate the prediction of the neural network for the initial number
  }

//Draw
  for (int i = 0; i <= (sizeof(sineNo) / sizeof(sineNo[0])); i++) {
    M5.Lcd.drawLine(i, 0, i, 135, TFT_BLACK); //Overpaint last visual
    M5.Lcd.drawLine(i, int(sineNo[i] * waveSize) + screenH/2-8, i, int(sineNo[i] * waveSize) + screenH/2+8, 0x3186); //
    M5.Lcd.drawLine(i, int(predictedNo[i] * waveSize) + screenH/2-1, i, int(predictedNo[i] * waveSize) + screenH/2+1, TFT_BLACK);
  }
}