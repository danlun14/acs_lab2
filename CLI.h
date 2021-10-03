#ifndef CLI_H
#define CLI_H
#define ARG_MAX_LENGHT 32
#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    int float_runs;
    int double_runs;
    int int_runs;
    char *opt;
    int prStatus;
} parsed_args;

int strcmp_m(const char *arg, const char *ava_arg);
parsed_args parse_arguments(int argc, char *argv[]);
void arg_init();

#endif