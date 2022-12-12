# Session 3 | 05.12.2022 – Background

***Disclaimer:*** *This page offers supporting material for an Interaction Design course held at [KISD](https://kisd.de) in the winter term 2022/23. Visit the [landing page](https://github.com/KISDinteractive/fundamentals22w) of this course for more information.*

# 3 (conitued from last session) Python Basics
We first finished the Python tutorial that we started in the last session before I broke my computer ;-) Docu therefore is a bit shorter today, the tutorial is pretty self explanatory though

# 4 Hello World
We then began to set up the system in wich we want to train a model that predicts a sine wave as a "Hello World" way to test if our setup is working.
- For this we boot a virtual kitegg server (you already got the credentials) with the option "(kisd-auto-kernels)"
- Next we want the Git (short: repo) available locally. So we type `git clone https://github.com/KISDinteractive/embedded_ai_22w.git` in a "Terminal" window of the JupyterLabs instance and hit the enter key.
- After a few secs the repo should appear in the preview of the filesystem on the left now as a directory called "embedded_ai_w22"
- We then type `embedded_ai_22w/sessions/Session4_HelloWorld/src/init-jupyter-kitegg.sh` in the terminal and hit enter. This runs some installations of dependencies that we need later on
- Last but not least we navigate to the same folder (sessions/Session4_HelloWorld/src/) by using the mouse in the file manager on the left of JupyterLabs and double click the ipynb file (a Jupyter Notebook) to open it. 
- If you get promptet which kernel to use, you select the " ... py37" kernel. If you do not get asked click on the kernelname in the upper right corner and the kernel prompt will open for you.
- Now run the first two cells of the Jupyter Notebook (press Shift + Enter) and check if the python and Tensorflow version are as described in the comments.

Next session we will proceed at this point.
