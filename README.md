# SIMIT
A brand new algorithm to detect border points in a 3D mesh. This algorithm was implemented in C/C++ and Python 3.0.

Requeriments:
Python 3.0
OpenCv 3.0+
C and C++ compiler
CUDA 9.0+
YOLO v3 installed
OpenGL any version

If you are in linux, follow these steps:
Download SIMIT folder and let darknet-master and the folder of SIMIT in the same directory;
You need to give permission to the .sh and .py files
To execute the code, you write ./rodarOpengl.sh renderizacaoOpengl renderizacaoOpengl inside the SIMIT folder

If you are in windows, you need to install and configure a visual studio environment for C, C++, OpenGL  and OpenCV.
To run the code, you need to configure all the path and commands in linux inside the files .sh, converting it to a bat file,or just use the new linux kernel in the windows 10 and won't be necessary to configure any .sh file.


Follow some keys and its features:
b-> run SIMIT auto
k -> run to just one perspective
i -> apply grounth truth after discovering border points
left click -> commands to movmente the mesh or scene
l - > bring camera and mesh to (0,0,0). you need bring it to (0,0,0) to perform the algorithm!
p -> apply tolo to the object in front the camera
o -> apply SIFT to the object in front the camera
z,x,c,v,Z,X and C move the mesh




