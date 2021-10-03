#ifndef tests_h
#define tests_h

enum
{
    N = 1024
};

void init_matrixi(int *a, int *b, int *c, int n);
void init_matrixf(float *a, float *b, float *c, int n);
void init_matrixd(double *a, double *b, double *c, int n);

void dgemm_int(int *a, int *b, int *c, int n);
void dgemm_float(float *a, float *b, float *c, int n);
void dgemm_double(double *a, double *b, double *c, int n);

#endif