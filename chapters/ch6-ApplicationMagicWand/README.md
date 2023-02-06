# Chapter 6 | Application: Magic Wand

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

The course was supposed to end with a practical project: An MCU with a position sensor (gyroscope & accelerometer) was to be used to remotely (via Bluetooth) control a slide show with a gesture movement. The following toolchain was discussed and then applied:

1. **Read and record gesture data:** An [Arduino sketch](src/Arduino_Sketches/record_imu_data) sends normalised measurements via serial to a computer. The Arduino serial monitor (or any other serial monitor) can then be used to view them, and copy and paste them into a text editor of your choice to save them as a comma-separated values (.csv) file. *Please note: In the new version 2.0.X of Arduino it is not possible to copy the whole history of the serial monitor. Use version 1.8.X for this*.
2. **Training a neural network:** In a [Jupyter Notebook](src/Jupyter_Notebook/TFGyroData.ipynb), very similar to the one used in the previous chapter, we trained a model small enough to fit on a MCU. To do this, place the recorded data in the form of two .csv files in the `datasets` directory and enter the names of the two categories in the settings cell of the notebook. The notebook is written to be used with two categories and would need some adjustments for more.
3. **Running the inference and sending the keypress (left/right) via bluetooth:** A second [Arduino sketch](src/Arduino_Sketches/record_imu_data) runs the model we just trained on a M5Stick, shows the results and sends the keypress via bluetooth once set up. All you have to do is copy and paste the `const unsigned char model[]` from the `model.h` file generated with the notebook into the `model.h` of the Arduino sketch and connect the M5Stick as Bluetooth keyboard.

The files are commented so that they can (hopefully) be used without further documentation.
