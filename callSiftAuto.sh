#!/bin/bash
cd ..
cd darknet-master
mv $2 ../projetoTcc
cd ..
cd projetoTcc
path=$1
python3 siftAuto.py $path
