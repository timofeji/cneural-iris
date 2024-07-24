#ifndef MODEL_H
#define MODEL_H

#include "math.h"

struct Matrix;

typedef enum
{
    SIGMOID,
    RELU,
} OPCODE;

typedef enum
{
    W,
    b,
    ACT,
    Z,
    D_ACT,
    D_W,
    D_B,
    D_Z,

    NEURON_PART_NUM
} NEURON_PART;

typedef int (*Activation)(int x);

typedef struct neuron_t
{
    float actv;
    float *out_weights;
    float bias;
    float z;

    float dactv;
    float *dw;
    float dbias;
    float dz;

} neuron;

typedef struct layer_t
{
    int num_neurons;
    float **weights;
    Activation  act; 
} layer;
layer createLayer(int n);

typedef struct layerDef_t
{
    int* num_neurons;
    OPCODE activation;
} layer_linear;


typedef struct neuralNetwork_t
{
    Matrix** matrices;
    layer* layers;
    int num_layers;
} neuralNetwork;

neuralNetwork* nn_init(const layer_linear nn_layers[]);
void nn_free(neuralNetwork* nn);


Matrix *forward(neuralNetwork *nn, Matrix* X);

#endif