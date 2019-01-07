#! /bin/bash
#script para compilar y ejecutar el código
g++ -g -std=c++0x main.cpp LLRBTree.h -o main && ./main #; echo $? # descomentar esta ultima parte para ver valor devuelto por el programa
