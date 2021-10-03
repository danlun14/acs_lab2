#include "CLI.h"

const char *arguments[ARG_MAX_LENGHT];

int strcmp_m(const char *arg, const char *ava_arg)
{
    int id = 0;
    while (*(arg + id) != '\0')
    {
        if (*(arg + id) != *(ava_arg + id))
        {
            //printf("id - %d\n", id);
            return -1;
        }
        id++;
    }
    return id;
}

void arg_init()
{
    arguments[0] = "--int-reps";
    arguments[1] = "--float-reps";
    arguments[2] = "--double-reps";
    arguments[3] = "-O0";
    arguments[4] = "-O1";
    arguments[5] = "-O2";
    arguments[6] = "-O3";
    arguments[7] = "--printf";
}

parsed_args parse_arguments(int argc, char *argv[])
{
    parsed_args runtimes;

    arg_init();

    runtimes.int_runs = 10;
    runtimes.float_runs = 10;
    runtimes.double_runs = 10;
    runtimes.opt = "-O0";
    runtimes.prStatus = 1;

    int _iarg = 0, _farg = 0, _darg = 0;
    int status = -1;
    int parsed_arg = 0;
    for (int i = 0; i < argc; i++)
    {
        //printf("%s\n", argv[i]);
        for (int j = 0; j < 8; j++)
        {
            status = strcmp_m(arguments[j], argv[i]);
            // printf("  s-%d\n", status);
            if (status != -1)
            {
                parsed_arg = atoi(argv[i] + status);
                // printf("  %d\n", parsed_arg);
                switch (j)
                {
                case 0:
                    if (_iarg != 1)
                    {
                        _iarg = 1;
                        runtimes.int_runs = parsed_arg;
                    }
                    break;
                case 1:
                    if (_farg != 1)
                    {
                        _farg = 1;
                        runtimes.float_runs = parsed_arg;
                    }
                    break;
                case 2:
                    if (_darg != 1)
                    {
                        _darg = 1;
                        runtimes.double_runs = parsed_arg;
                    }
                    break;

                case 3:
                    runtimes.opt = "-O0";
                    break;
                case 4:
                    runtimes.opt = "-O1";
                    break;
                case 5:
                    runtimes.opt = "-O2";
                    break;
                case 6:
                    runtimes.opt = "-O3";
                    break;

                case 7:
                    runtimes.prStatus = parsed_arg;
                    break;
                }
            }
        }
        //printf(" %d\n", j);

        //printf("%d\n", i);
    }
    return runtimes;
}