#! /bin/bash
#script para compilar y ejecutar el código
g++ -g *.cpp *.h -o main && ./main #; echo $?
