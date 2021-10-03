#include "tests.h"
#include <stdlib.h>
#include <time.h>

void init_matrixi(int *a, int *b, int *c, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(a + i * n + j) = rand() % 6;
            *(b + i * n + j) = rand() % 6;
            *(c + i * n + j) = 0;
        }
    }
}

void init_matrixf(float *a, float *b, float *c, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(a + i * n + j) = (float)(rand() % 6000 / 1000);
            *(b + i * n + j) = (float)(rand() % 6000 / 1000);
            *(c + i * n + j) = (float)0;
        }
    }
}

void init_matrixd(double *a, double *b, double *c, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(a + i * n + j) = (double)(rand() % 6000000 / 1000000);
            *(b + i * n + j) = (double)(rand() % 6000000 / 1000000);
            *(c + i * n + j) = (double)0;
        }
    }
}

void dgemm_int(int *a, int *b, int *c, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
            {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
            }
        }
    }
}

void dgemm_float(float *a, float *b, float *c, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++) //120000000000
    {
        for (k = 0; k < n; k++) //60000000
        {
            for (j = 0; j < n; j++) //30000
            {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j); //15
            }
        }
    }
}

void dgemm_double(double *a, double *b, double *c, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
            {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
            }
        }
    }
}