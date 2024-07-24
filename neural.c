#include "neural.h"

#define m_(NEURON_PART) nn->matrices[NEURON_PART + l]

layer createLayer(int n)
{
    layer l;
    return l;
}

neuralNetwork* nn_init(const layer_linear defs[])
{
    // nn.layers = (layer *)malloc(num_layers * sizeof(layer));

    neuralNetwork nn;
    nn.num_layers = sizeof(defs) / sizeof(defs);
    nn.matrices = (Matrix *)malloc(NEURON_PART_NUM * nn.num_layers * sizeof(Matrix));

    for (int l = 0; l < nn.num_layers - 1; l++)
    {
        int shape[] = {defs[l].num_neurons, defs[l + 1].num_neurons};
        for (int j = 0; j < NEURON_PART_NUM - 1; l++)
        {
            nn.matrices[l+j] = m_init(shape[0], shape[1], true);
        }


            // //Weights
            // Matrix *b = m_init(shape[1], 1, true);

            // //Biases
            // nn.matrices =
    }

    return &nn;
}

void nn_free(neuralNetwork* nn)
{

}

// void update_weights(void)
// {
//     int i,j,k;

//     for(i=0;i<num_layers-1;i++)
//     {
//         for(j=0;j<num_neurons[i];j++)
//         {
//             for(k=0;k<num_neurons[i+1];k++)
//             {
//                 // Update Weights
//                 lay[i].neu[j].out_weights[k] = (lay[i].neu[j].out_weights[k]) - (alpha * lay[i].neu[j].dw[k]);
//             }
            
//             // Update Bias
//             lay[i].neu[j].bias = lay[i].neu[j].bias - (alpha * lay[i].neu[j].dbias);
//         }
//     }   
// }

// void compute_gradients(int p)
// {
//     int i,j,k;

//     // Output Layer
//     for(j=0;j<num_neurons[num_layers-1];j++)
//     {           
//         lay[num_layers-1].neu[j].dz = (lay[num_layers-1].neu[j].actv - desired_outputs[p][j]) * (lay[num_layers-1].neu[j].actv) * (1- lay[num_layers-1].neu[j].actv);

//         for(k=0;k<num_neurons[num_layers-2];k++)
//         {   
//             lay[num_layers-2].neu[k].dw[j] = (lay[num_layers-1].neu[j].dz * lay[num_layers-2].neu[k].actv);
//             lay[num_layers-2].neu[k].dactv = lay[num_layers-2].neu[k].out_weights[j] * lay[num_layers-1].neu[j].dz;
//         }
            
//         lay[num_layers-1].neu[j].dbias = lay[num_layers-1].neu[j].dz;           
//     }

//     // Hidden Layers
//     for(i=num_layers-2;i>0;i--)
//     {
//         for(j=0;j<num_neurons[i];j++)
//         {
//             if(lay[i].neu[j].z >= 0)
//             {
//                 lay[i].neu[j].dz = lay[i].neu[j].dactv;
//             }
//             else
//             {
//                 lay[i].neu[j].dz = 0;
//             }

//             for(k=0;k<num_neurons[i-1];k++)
//             {
//                 lay[i-1].neu[k].dw[j] = lay[i].neu[j].dz * lay[i-1].neu[k].actv;    
                
//                 if(i>1)
//                 {
//                     lay[i-1].neu[k].dactv = lay[i-1].neu[k].out_weights[j] * lay[i].neu[j].dz;
//                 }
//             }

//             lay[i].neu[j].dbias = lay[i].neu[j].dz;
//         }
//     }
// }


Matrix *forward(neuralNetwork *nn, Matrix* X)
{
    //input activations
    nn->matrices[ACT] = X;

    for (int l = 1; l < nn->num_layers; l++)
    {
        m_(Z) = m_add(m_mul(m_(W), m_(ACT-1)), m_(b))
        m_(ACT) = 
    }
}

