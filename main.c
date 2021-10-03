#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hpctimer.h"
#include "CLI.h"
#include "tests.h"

#define POINTS_TRESHOLD 1000000

typedef struct
{
    char *PModel;
    char *Task;
    char *OpType;
    long InsCount;
    char *OptFlag;
    char *Timer;
    double Time;
    int LNum;
    double AvTime;
    double AbsError;
    double RelError;
    long TaskPerf;
} out_res; //11(5 st 6 on)

void print_out_res(out_res node)
{
    printf("PModel: %s; ", node.PModel);
    printf("Task: %s; ", node.Task);
    printf("OpType: %s; ", node.OpType);
    printf("InstCount: %ld; ", node.InsCount);
    printf("OptFlag: %s; ", node.OptFlag);
    printf("Time: %.4lf; ", node.Time);
    printf("LNum: %d; ", node.LNum);
    printf("AvTime: %.4lf; ", node.AvTime);
    printf("AbsError: %.4lf; ", node.AbsError);
    printf("RelError: %.4lf %; ", node.RelError);
    printf("TaskPerf: %ld;\n", node.TaskPerf);
}

void print_out_res_file(out_res node, FILE *out_file)
{
    fprintf(out_file, "PModel: %s; ", node.PModel);
    fprintf(out_file, "Task: %s; ", node.Task);
    fprintf(out_file, "OpType: %s; ", node.OpType);
    fprintf(out_file, "InstCount: %ld; ", node.InsCount);
    fprintf(out_file, "OptFlag: %s; ", node.OptFlag);
    fprintf(out_file, "Time: %.4lf; ", node.Time);
    fprintf(out_file, "LNum: %d; ", node.LNum);
    fprintf(out_file, "AvTime: %.4lf; ", node.AvTime);
    fprintf(out_file, "AbsError: %.4lf; ", node.AbsError);
    fprintf(out_file, "RelError: %.4lf %; ", node.RelError);
    fprintf(out_file, "TaskPerf: %ld;\n", node.TaskPerf);
}

char output_buf[256];

int Ai[N * N], Bi[N * N], Ci[N * N];
float Af[N * N], Bf[N * N], Cf[N * N];
double Ad[N * N], Bd[N * N], Cd[N * N];

int main(int argc, char *argv[])
{
    parsed_args pargs = parse_arguments(argc, argv);
    printf("Print - %d\n", pargs.prStatus);
    char *PName = argv[1];
    if (pargs.prStatus != 0)
    {
        printf("Optimization: %s\n", pargs.opt);
        printf("Processor name:%s\n", PName);
        printf("Operations count: ~%ld\n", (long)N * (long)N * (long)N * (long)2 * (long)2 * (long)2 * (long)15);
        printf("dgemm_int repeats: %d\ndgemm_float repeats:%d\ndgemm_int repeats:%d\n", pargs.int_runs, pargs.float_runs, pargs.double_runs);
    }

    double t = hpctimer_getwtime();
    init_matrixi(Ai, Bi, Ci, N);
    t = hpctimer_getwtime() - t;
    if (pargs.prStatus != 0)
    {
        printf("Init INT matrix - %lf\n", t);
    }

    t = hpctimer_getwtime();
    init_matrixf(Af, Bf, Cf, N);
    t = hpctimer_getwtime() - t;
    if (pargs.prStatus != 0)
    {
        printf("Init FLOAT matrix - %lf\n", t);
    }

    t = hpctimer_getwtime();
    init_matrixd(Ad, Bd, Cd, N);
    t = hpctimer_getwtime() - t;
    if (pargs.prStatus != 0)
    {
        printf("Init DOUBLE matrix - %lf\n", t);
    }

    double t_all = 0, t_avr = 0;
    FILE *result_file = fopen("results.csv", "a");
    //run int dgemm
    if (pargs.prStatus != 0)
    {
        printf("*************INT DGEMM*************\n");
    }
    out_res int_dgemm[pargs.int_runs];
    for (int i = 0; i < pargs.int_runs; i++)
    {

        t = hpctimer_getwtime();
        dgemm_int(Ai, Bi, Ci, N);
        t = hpctimer_getwtime() - t;
        int_dgemm[i].Time = t;
        t_all += t;
        if (pargs.prStatus != 0)
        {
            printf("INT DGEMM> Time of %d run: %lf\n", i, t);
        }
    }
    t_avr = t_all / pargs.int_runs;
    for (int i = 0; i < pargs.int_runs; i++)
    {
        int_dgemm[i].PModel = PName;
        int_dgemm[i].Task = "DGEMM";
        int_dgemm[i].OpType = "INT";
        int_dgemm[i].InsCount = N * N * N * 2L * 2L * 2L * 15L;
        int_dgemm[i].OptFlag = pargs.opt;
        int_dgemm[i].Timer = "hpctimer_getwtime()";
        int_dgemm[i].LNum = i;
        int_dgemm[i].AvTime = t_avr;

        int_dgemm[i].AbsError = fabs(int_dgemm[i].AvTime - int_dgemm[i].Time);
        int_dgemm[i].RelError = int_dgemm[i].AbsError / int_dgemm[i].AvTime;

        int_dgemm[i].TaskPerf = int_dgemm[i].InsCount / int_dgemm[i].Time / POINTS_TRESHOLD;

        print_out_res_file(int_dgemm[i], result_file);
        if (pargs.prStatus != 0)
        {
            print_out_res(int_dgemm[i]);
        }
    }
    t_all = 0;
    t_avr = 0;
    //run float dgemm
    if (pargs.prStatus != 0)
    {
        printf("\n*************FLOAT DGEMM*************\n");
    }
    out_res float_dgemm[pargs.float_runs];
    for (int i = 0; i < pargs.float_runs; i++)
    {

        t = hpctimer_getwtime();
        dgemm_float(Af, Bf, Cf, N);
        t = hpctimer_getwtime() - t;
        float_dgemm[i].Time = t;
        t_all += t;
        if (pargs.prStatus != 0)
        {
            printf("FLOAT DGEMM> Time of %d run: %lf\n", i + 1, t);
        }
    }
    t_avr = t_all / pargs.float_runs;
    for (int i = 0; i < pargs.float_runs; i++)
    {
        float_dgemm[i].PModel = PName;
        float_dgemm[i].Task = "DGEMM";
        float_dgemm[i].OpType = "FLOAT";
        float_dgemm[i].InsCount = N * N * N * 2L * 2L * 2L * 15L;
        float_dgemm[i].OptFlag = pargs.opt;
        float_dgemm[i].Timer = "hpctimer_getwtime()";
        float_dgemm[i].LNum = i;
        float_dgemm[i].AvTime = t_avr;

        float_dgemm[i].AbsError = fabs(float_dgemm[i].AvTime - float_dgemm[i].Time);
        float_dgemm[i].RelError = float_dgemm[i].AbsError / float_dgemm[i].AvTime;

        float_dgemm[i].TaskPerf = float_dgemm[i].InsCount / float_dgemm[i].Time / POINTS_TRESHOLD;

        print_out_res_file(float_dgemm[i], result_file);
        if (pargs.prStatus != 0)
        {
            print_out_res(float_dgemm[i]);
        }
    }
    t_all = 0;
    t_avr = 0;
    //run double dgemm
    if (pargs.prStatus != 0)
    {
        printf("\n*************DOUBLE DGEMM*************\n");
    }
    out_res double_dgemm[pargs.double_runs];
    for (int i = 0; i < pargs.double_runs; i++)
    {

        t = hpctimer_getwtime();
        dgemm_double(Ad, Bd, Cd, N);
        t = hpctimer_getwtime() - t;
        double_dgemm[i].Time = t;
        t_all += t;
        if (pargs.prStatus != 0)
        {
            printf("DOUBLE DGEMM> Time of %d run: %lf\n", i, t);
        }
    }
    t_avr = t_all / pargs.double_runs;
    for (int i = 0; i < pargs.double_runs; i++)
    {
        double_dgemm[i].PModel = PName;
        double_dgemm[i].Task = "DGEMM";
        double_dgemm[i].OpType = "DOUBLE";
        double_dgemm[i].InsCount = N * N * N * 2L * 2L * 2L * 15L;
        double_dgemm[i].OptFlag = pargs.opt;
        double_dgemm[i].Timer = "hpctimer_getwtime()";
        double_dgemm[i].LNum = i;
        double_dgemm[i].AvTime = t_avr;

        double_dgemm[i].AbsError = fabs(double_dgemm[i].AvTime - double_dgemm[i].Time);
        double_dgemm[i].RelError = double_dgemm[i].AbsError / double_dgemm[i].AvTime;

        double_dgemm[i].TaskPerf = double_dgemm[i].InsCount / double_dgemm[i].Time / POINTS_TRESHOLD;
        print_out_res_file(double_dgemm[i], result_file);
        if (pargs.prStatus != 0)
        {
            print_out_res(double_dgemm[i]);
        }
    }
    FILE *Opt_gp;
    t_all = 0;
    t_avr = 0;
    if (strcmp_m(pargs.opt, "-O0") != -1)
    {
        Opt_gp = fopen("Opt0.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(Opt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        FILE *OpTypeInt_gp, *OpTypeFloat_gp, *OpTypeDouble_gp;
        FILE *v1, *v2;
        OpTypeInt_gp = fopen("int.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeInt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        OpTypeFloat_gp = fopen("float.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeFloat_gp, "%d %ld\n", i, float_dgemm[i].TaskPerf);
        }
        OpTypeDouble_gp = fopen("double.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeDouble_gp, "%d %ld\n", i, double_dgemm[i].TaskPerf);
        }
    }
    else if (strcmp_m(pargs.opt, "-O1") != -1)
    {
        Opt_gp = fopen("Opt1.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(Opt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        FILE *OpTypeInt_gp, *OpTypeFloat_gp, *OpTypeDouble_gp;
        FILE *v1, *v2;
        OpTypeInt_gp = fopen("int1.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeInt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        OpTypeFloat_gp = fopen("float1.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeFloat_gp, "%d %ld\n", i, float_dgemm[i].TaskPerf);
        }
        OpTypeDouble_gp = fopen("double1.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeDouble_gp, "%d %ld\n", i, double_dgemm[i].TaskPerf);
        }
    }
    else if (strcmp_m(pargs.opt, "-O2") != -1)
    {
        Opt_gp = fopen("Opt2.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(Opt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        FILE *OpTypeInt_gp, *OpTypeFloat_gp, *OpTypeDouble_gp;
        FILE *v1, *v2;
        OpTypeInt_gp = fopen("int2.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeInt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        OpTypeFloat_gp = fopen("float2.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeFloat_gp, "%d %ld\n", i, float_dgemm[i].TaskPerf);
        }
        OpTypeDouble_gp = fopen("double2.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeDouble_gp, "%d %ld\n", i, double_dgemm[i].TaskPerf);
        }
    }
    else if (strcmp_m(pargs.opt, "-O3") != -1)
    {
        Opt_gp = fopen("Opt3.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(Opt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        FILE *OpTypeInt_gp, *OpTypeFloat_gp, *OpTypeDouble_gp;
        FILE *v1, *v2;
        OpTypeInt_gp = fopen("int3.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeInt_gp, "%d %ld\n", i, int_dgemm[i].TaskPerf);
        }
        OpTypeFloat_gp = fopen("float3.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeFloat_gp, "%d %ld\n", i, float_dgemm[i].TaskPerf);
        }
        OpTypeDouble_gp = fopen("double3.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            fprintf(OpTypeDouble_gp, "%d %ld\n", i, double_dgemm[i].TaskPerf);
        }
    }
    printf("All TaskPerf divided by %d\n", POINTS_TRESHOLD);
    return 0;
}