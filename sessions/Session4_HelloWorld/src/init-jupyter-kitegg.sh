#!/bin/bash
# only /home is persistent, so we need to store envs and kernels here
# create jupyter config file so that kernels will stored in /home
echo -e "{\n  \"CondaKernelSpecManager\": {\n    \"kernelspec_path\": \"--user\"\n  }\n}" >> /home/jovyan/.jupyter/jupyter_config.json
# define a path in /home for conda envs as well
conda config --add envs_dirs /home/jovyan/.conda_envs 

# install tool that auto creates kernels from conda envs
# conda install nb_conda_kernels -y 

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

# install IPython kernel (inside of new env!) to make it visible
conda install ipykernel -y

# update jupyter - otherwise kernel is not recognized (bugfix)
pip install --upgrade jupyter_client
pip install --upgrade jupyter_server

# leave conda env
conda deactivate

# check if the kernel appears in both:
python -m nb_conda_kernels list
jupyter kernelspec list

#THE END - CMD + R to reload browser window!