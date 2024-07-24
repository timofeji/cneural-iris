#include <stdio.h>
#include <stdlib.h>

#include "neural.h"


typedef struct {
    float SepalLengthCm;
    float SepalWidthCm;
    float PetalLengthCm;
    float PetalWidthCm;
    int Label;
} IrisData;

void shuffleData(IrisData *data, int count)
{
    srand((unsigned int)time(NULL));
    for (int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        IrisData temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}
void splitData(IrisData *data, int count, float trainRatio, IrisData **trainData, int *trainCount, IrisData **evalData, int *evalCount)
{
    *trainCount = (int)(count * trainRatio);
    *evalCount = count - *trainCount;

    *trainData = (IrisData *)malloc(*trainCount * sizeof(IrisData));
    *evalData = (IrisData *)malloc(*evalCount * sizeof(IrisData));

    for (int i = 0; i < *trainCount; i++)
    {
        (*trainData)[i] = data[i];
    }

    for (int i = 0; i < *evalCount; i++)
    {
        (*evalData)[i] = data[i + *trainCount];
    }
}

void loadData(const char *fileName, IrisData *data, int *count)
{
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")) != 0)
    {
        printf("failed to open file");
        exit(0);
    }

    const char labels[3][50] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

    char line[256];
    fgets(line, sizeof(line), file); // skip csv header
    while (fgets(line, sizeof(line), file))
    {
        int id;
        float sepalLength, sepalWidth, petalLength, petalWidth;
        char species[50];

        sscanf_s(line, "%d,%f,%f,%f,%f,%49s",
                 &id,
                 &sepalLength,
                 &sepalWidth,
                 &petalLength,
                 &petalWidth,
                 species, (unsigned)_countof(species));

        data[*count].SepalLengthCm = sepalLength;
        data[*count].SepalWidthCm = sepalWidth;
        data[*count].PetalLengthCm = petalLength;
        data[*count].PetalWidthCm = petalWidth;


        for (int i = 0; i < 3; i++)
        {
            if(strcmp(species, labels[i]) == 0)
            {
                data[*count].Label = i;
                break;
            }
        }
        (*count)++;
    }

    fclose(file);
}

int main()
{
    IrisData data[150];
    IrisData *trainData;
    IrisData *evalData;

    char fileName[] = "data.csv";
    int count, trainCount, evalCount;
    float trainRatio = 0.8; // 80% training, 20% evaluation

    loadData(fileName, data, &count);
    shuffleData(data, count);
    splitData(data, count, trainRatio, &trainData, &trainCount, &evalData, &evalCount);

    ///////DEFINE MODEL
    layer_linear input;
    input.num_neurons = 4;
    input.activation = RELU;

    layer_linear hidden;
    input.num_neurons = 12;
    input.activation = RELU;

    layer_linear output;
    input.num_neurons = 3;
    input.activation = SIGMOID;

    layer_linear nn_layers[] = {input, hidden, output};
    neuralNetwork* nn = nn_init(nn_layers);

    // TRAINING
    const float EPSILON = .1f; // learning rate
    for (int i = 0; i < trainCount; i++)
    {
        float label[3] = {0, 0, 0};
        for (int j = 0; j < 3; j++)
        {
            label[j] = trainData[i].Label == j ? 1.0 : 0.0;
        }
        Matrix *Y = m_init(3, 1, false);
        m_fill(Y, label);

        float x[] = {trainData[i].PetalLengthCm,
                     trainData[i].PetalWidthCm,
                     trainData[i].SepalLengthCm,
                     trainData[i].SepalWidthCm};
        Matrix *X = m_init(4, 1, false);
        m_fill(X, x);

        Matrix *yHat = forward(nn, X);
        Matrix *Cost = compute_cost(yHat, Y);

        compute_gradients(nn, Cost);

        m_free(X);
        m_free(Y);
    }

    // float x = sigma(-2.0f);
    // printf("%f", x);
    //EVAL
    for (int i = 0; i < evalCount; i++)
    {
    }

    free(trainData);
    free(evalData);

    return 0;
}