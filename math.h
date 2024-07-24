#ifndef MATH_H
#define MATH_H

#define NUM_EULER 2.71828182845904523536f // e

#define true 1
#define false 0

float sigma(float x);
float d_sigma(float x);
float relu(float x);


float randSample(float low, float high);

/// Matrix MATH
typedef struct {
    float** vals;
    int rows;
    int cols;
} Matrix;

Matrix* m_init(int rows, int cols, char bRand);
Matrix* m_mul(Matrix* A, Matrix* B);
Matrix* m_sub(Matrix* A, Matrix* B);
void m_fill(Matrix *m, float* vals);
void m_print(Matrix *m);
void m_free(Matrix *m);

#endif