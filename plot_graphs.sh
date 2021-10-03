#!/bin/bash

cpu_name=" $(lscpu | grep 'Имя модели' | awk '{print $3_$4_$5_$6}')"

gcc -o dgemm_tests main.c CLI.c hpctimer.c tests.c -O0
./dgemm_tests $cpu_name -O0 --printf0
gnuplot OPTYPE_with_O0.plt

gcc -o dgemm_tests main.c CLI.c hpctimer.c tests.c -O1
./dgemm_tests $cpu_name -O1 --printf0
gnuplot OPTYPE_with_O1.plt

gcc -o dgemm_tests main.c CLI.c hpctimer.c tests.c -O2
./dgemm_tests $cpu_name -O2 --printf0
gnuplot OPTYPE_with_O2.plt

gcc -o dgemm_tests main.c CLI.c hpctimer.c tests.c -O3
./dgemm_tests $cpu_name -O3 --printf0
gnuplot OPTYPE_with_O3.plt

gnuplot optPerf_int.plt