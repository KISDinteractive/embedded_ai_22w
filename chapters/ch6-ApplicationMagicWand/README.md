# Chapter 6 | Application: Magic Wand

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

Towards the end of the course the learning was to be implemented in a practical project: An MCU with a position sensor (gyroscope & accelerometer) was to be used to remotely (via Bluetooth) control a slide show through a gesture movement. The following toolchain was discussed together for this purpose and then applied:

1. **Reading and recording gesture data:** an [Arduino sketch](src/Arduino_Sketches/record_imu_data) sends normalized measurements via serial to a computer. The Arduino serial monitor (or any other serial monitor) can then be used to display them and copy paste them into a text editor of your choice to save it as a comma separated values (.csv) file. *Attention: As of January 2023, it is not possible to copy out the entire history of the serial monitor in the new 2.0.X version of Arduino. Use version 1.8.X for this*
2. **Training a neural network:** in a [Jupyter Notebook](src/Jupyter_Notebook/TFGyroData.ipynb) very simliar to those being used in the previous chapter we trained a model small enough to fit on a MCU. To do so place the recorded data in form of two .csv files in the `datasets` directory and enter names of the two categories in the settings cell of the notebook. The Notebook is written to be used with two categories and would need some adjustments for more.
3. **Running the Inference and Sending left/right key pressed via Bluetooth:** a second [Arduino sketch](src/Arduino_Sketches/record_imu_data) runs the model that we just trained on a M5Stick, shows the results and sends the key-command via bluetooth once set up. You only have to copy paste the `const unsigned char model[]` from the `model.h` file generated with the notebook into the `model.h` of the Arduino sketch and connect the M5Stick as Bluetooth keyboard.

The respective files are commented accordingly so that they can be processed without further documentation.
