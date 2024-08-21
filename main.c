#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "neural.h"
const char target_labels[3][50] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

#define BUFFER_SIZE 65536

//-- Id,SepalLengthCm,SepalWidthCm,PetalLengthCm,PetalWidthCm,Species
void parseLine(const char *line, Matrix **outData, Matrix **outLabel, int dataIndex)
{
    //skip ID col
    const char* start = strchr(line, ',') + 1;

    float dataArr[4];
    float labelArr[3]; 
    int col = 0;
    while (*start)
    {
        const char *end = strchr(start, ',');
        if (!end)
        {
            end = start + strlen(start);
        }

        size_t len = end - start;
        char *token = (char *)malloc(len + 1);

        strncpy(token, start, len);
        token[len] = '\0';

        if (col < 4)
        {
            char *p_end;
            float val = strtof(token, &p_end);
            free(token);

            dataArr[col] = val;
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (strcmp(token, target_labels[i]) == 0)
                {
                    labelArr[i] = 1.0;
                }
            }
        }

        if (*end)
        {
            start = end + 1;
        }
        else
        {
            break;
        }  


        col++;
    }

    Matrix *dataMat = m_init(4, 1, false);
    m_fill(dataMat, dataArr);
    outData[dataIndex] = dataMat;

    Matrix *labelMat = m_init(3, 1, false);
    m_fill(labelMat, labelArr);
    outLabel[dataIndex] = labelMat;
}

void loadData(const char *fileName, Matrix** data, Matrix** label)
{
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")) != 0)
    {
        printf("%s(): failed to open file %s", __func__, fileName);
        exit(0);
    }

    int dataCount = 0;

    char buffer[BUFFER_SIZE];
    while (true)
    {
        size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, file);
        buffer[bytesRead] = '\0';

        char *line = strtok(buffer, "\n");
        line = strtok(NULL, "\n"); // Skip CSV header

        while (line != NULL)
        {
            char *lineBuffer = malloc(strlen(line) + 1);
            strcpy(lineBuffer, line);

            parseLine(lineBuffer, data, label, dataCount);

            free(lineBuffer);
            line = strtok(NULL, "\n");

            dataCount++;
        }

        if (feof(file))
            break;
    }
    fclose(file);
}

int main()
{
    // we know that we have 150 data points
    const char fileName[] = "data.csv";
    const int dataCount = 150;
    Matrix **dataArr = malloc(sizeof(Matrix *) * dataCount);
    Matrix **labelArr = malloc(sizeof(Matrix *) * dataCount);

    loadData(fileName, dataArr, labelArr);


    // DEFINE MODEL
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

    for (int i = 0; i < dataCount; i++)
    {
        Matrix *X = *(dataArr + i);
        Matrix *Y = *(labelArr + i);
        // Matrix *yHat = forward(nn, X);
        // // Matrix *Cost = compute_cost(yHat, Y);

        // compute_gradients(nn, Cost);
    }

    for (int i = 0; i < dataCount; i++)
    {
        m_free(dataArr[i]);
        m_free(labelArr[i]);
    }

    free(dataArr);
    free(labelArr);

    return 0;
}