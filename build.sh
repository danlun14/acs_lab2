#!/bin/bash

gcc -o dgemm_tests main.c CLI.c hpctimer.c tests.c $1 

cpu_name=" $(lscpu | grep 'Имя модели' | awk '{print $3_$4_$5_$6}')"

./dgemm_tests $cpu_name $1 $2 $3 $4