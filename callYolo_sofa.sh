#!/bin/bash

mv $1 ../darknet-master
cd ..
cd darknet-master
path=$1
./darknet detector test obj_sofa.data yolo-obj_sofa.cfg yolo-obj_best_sofa.weights -ext_output ${path} >> ${path}.txt
mv predictions.jpg ${path}.jpg
