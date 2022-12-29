#!/bin/bash

cp ../materials/linters/.clang-format .

clang-format -n controller/*
clang-format -n parser/*
clang-format -n test/*
clang-format -n Widget/*.cpp
clang-format -n matrixlib/s21_matrix.c
clang-format -n matrixlib/s21_matrix.h


clang-format -i controller/*
clang-format -i parser/*
clang-format -i test/*
clang-format -i Widget/*.cpp
clang-format -i matrixlib/s21_matrix.c
clang-format -i matrixlib/s21_matrix.h

rm .clang-format 


