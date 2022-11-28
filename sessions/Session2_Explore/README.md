# Session 2 | 28.11.2022 – Explore

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

# 2.1 Train Model in Predefined Setting

In Session 2 we did some practical experiments with a ESP32-CAM board. These are the steps we went through, **which can only be reproduced with the physical board available and connected to the coputer via cable:**

## Flash Code to ESP

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Do to *Settings → "Additional boards manager URLs" →* enter: https://dl.espressif.com/dl/package_esp32_index.json
3. Go to *Tools → Board: → Boards Manager...* and search for "esp32". Install *esp32 by Espressif Systems* by klicking on "install" ![esp-boards](img/esp-boards.jpg)
4. Download the prepared [code file](/src/ESP32-CAM_Teachable_Machine/ESP32-CAM_Teachable_Machine.ino). Fasted way for beginners: click on "raw" → select all code & copy → open new Arduino file → paste code inside
5. Upload
6. Check Serial Manager (baud rate = 115200). There should be a "IP address is...", in case the board managed to open a connection to the WiFi
7. Make a note for the IP and call it with your browser. We will call it YOURIP from now on.
8. Klick on "start stream" and check if you can see the live video stream from the ESP

## Set up OBS

- Download and install [OBS](https://obsproject.com)
- In OBS: delete all sources, add a "browser source" and enter: http://YOURIP:81/stream (replace YOURIP with the actual IP)
- Position the stream by dragging and resizing.
- Click on "Activate virtual Camera" on the bottom right

## Train Model via Teachable Machine

- Open a new image project on [Teachable Machine](https://teachablemachine.withgoogle.com/train/image)
- Select the virtual OBS webcam as Input
- Add Data for the two (or more) classes and train the model (details have been discussed in the course)
- Test if the model works with the testing function of Techable Machine (appearing on the right hand side after training a model)
- Click on *export model → uploade model → copy link*

## Run Inference

- Finally go to http://YOURIP again and enter the link you have just copied from Teachable Machine into the "load model" field and click on *start detection*

Now your browser (and the machine running the browser) runs the model by using the image stream from the ESP and the LED on the ESP turns on if the first class of the trained ones gets detected. Note that in the moment you close the brwoser window, the ESP won't change the LED anymore as the calculation has been done in your browser. This is a classic Edge AI fake that we can use e.g. to make *Living Object* prototypes...

