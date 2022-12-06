#!/bin/bash

# This script initializes a few things so that a JupyterLabs Instance on the KITeGG Server can be used right away to train tensorflow models for MCUs
# As we want to use the Arduion TinyML Eloquent library (https://eloquentarduino.com/libraries/eloquent-tinyml/) we need to use tf 2.1.1
# To do so the script makes conda envs and kernels persistent (so that they are still there after a reboot), creates a new conda env 
# with the respective python version (3.7) and installs some packages (tensorflow, protobuf, matplotlib, ipykernel).
# To prevent a versioning-bug, it then updates jupyter and in the end lists all available kernels as a cross-check.

# ______ Make conda envs and jupyter kernel persistent ______
# only /home is persistent, so we need to store envs and kernels here
# create jupyter config file so that kernels will stored in /home
echo -e "{\n  \"CondaKernelSpecManager\": {\n    \"kernelspec_path\": \"--user\"\n  }\n}" >> /home/jovyan/.jupyter/jupyter_config.json
# define a path in /home for conda envs as well
conda config --add envs_dirs /home/jovyan/.conda_envs 

# ______ Create conda env with respective dependencies ______
# create conda env. Here w python 3.7 (supporting TF 2.1)
conda create -n py37 python=3.7 -y 
# configure conda for bash (needed for activation)
conda init bash
# restart terminal (needed for activation)
source ~/.bashrc
# activate new env (with full path at the first time)
conda activate /home/jovyan/.conda_envs/py37
#install dependencies (downgrade TF, and protobuf)
pip install tensorflow==2.1.1
pip install protobuf==3.20.* 
pip install pip matplotlib
pip install tqdm
# install IPython kernel (inside of new env!) to make it visible
conda install ipykernel -y

# ______ Bugfix: update jupyter to prevent kernels not loading correctly ______
# update jupyter - otherwise kernel is not recognized (bugfix)
pip install --upgrade jupyter_client
pip install --upgrade jupyter_server

# ______ Check if Jupyter can see the newly created env and kernel ______
# leave conda env
conda deactivate
# check if the kernel appears in both:
python -m nb_conda_kernels list
jupyter kernelspec list

#THE END