# SIMIT
A brand new algorithm to detect border points in a 3D mesh. This algorithm was implemented in C/C++ and Python 3.0.

Requeriments:<br/>
Python 3.0<br/>
OpenCv 3.0+<br/>
C and C++ compiler<br/>
CUDA 9.0+<br/>
YOLO v3 installed<br/>
OpenGL any version<br/>

If you are in linux, follow these steps:<br/>
Download SIMIT folder and let darknet-master and the folder of SIMIT in the same directory;<br/>
You need to give permission to the .sh and .py files<br/>
To execute the code, you write ./rodarOpengl.sh renderizacaoOpengl renderizacaoOpengl inside the SIMIT folder<br/>

If you are in windows, you need to install and configure a visual studio environment for C, C++, OpenGL  and OpenCV.<br/>
To run the code, you need to configure all the path and commands in linux inside the files .sh, converting it to a bat file,or just use the new linux kernel in the windows 10 and won't be necessary to configure any .sh file.<br/>


Follow some keys and its features:<br/>
b-> run SIMIT auto<br/>
k -> run to just one perspective<br/>
i -> apply grounth truth after discovering border points<br/>
left click -> commands to movmente the mesh or scene<br/>
l - > bring camera and mesh to (0,0,0). you need bring it to (0,0,0) to perform the algorithm!<br/>
p -> apply tolo to the object in front the camera<br/>
o -> apply SIFT to the object in front the camera<br/>
z,x,c,v,Z,X and C move the mesh<br/>




