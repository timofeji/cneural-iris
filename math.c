
#include <stdlib.h>
#include <math.h>
#include "math.h"

float sigma(float x)
{
    return (1 / (1 + pow(NUM_EULER, -x)));
}

float d_sigma(float x)
{
    return sigma(x) * (1 - sigma(x));
}

float relu(float x)
{
    return x < 0 ? 0 : x;
}


float randSample(float low, float high)
{
    return 0.0f;
}

Matrix *m_init(int rows, int cols, char bRand)
{
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->vals = malloc(rows * sizeof(float *));

    // if(bRand)
    //     srand(time(0));

    for (int i = 0; i < rows; i++)
    {
        m->vals[i] = malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++)
        {
            m->vals[i][j] = bRand ? (float)(rand()) / (float)(RAND_MAX) : 0.0f;
        }
    }

    return m;
}

Matrix *m_mul(Matrix *A, Matrix *B)
{
    Matrix *C = m_init(A->rows, B->cols, false);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->cols; j++)
        {
            for (int k = 0; k < B->rows; k++)
            {
                C->vals[i][j] += A->vals[i][k] * B->vals[k][j];
            }
        }
    }

    return C;
}

Matrix *m_sub(Matrix *A, Matrix *B)
{
    Matrix *C = m_init(A->rows, A->cols, false);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->cols; j++)
        {
            C->vals[i][j] = A->vals[i][j] - B->vals[i][j];
        }
    }

    return C;
}

void m_fill(Matrix *m, float *vals)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            m->vals[i][j] = *(vals + j + i * m->cols);
        }
    }
}

void m_print(Matrix *m)
{
    printf("\n");
    printf("Matrix[\n");
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%f,", m->vals[i][j]);
        }
        printf("\n");
    }
    printf("]");
    printf("\n");
}

void m_free(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->vals[i]);
    }
    free(m->vals);
    free(m);
    m = NULL;
}