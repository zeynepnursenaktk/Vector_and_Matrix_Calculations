/*
 * @file matrixLib.c
 * @description Matrix fonksiyonlarının gövdelerinin bulunduğu dosya
 * @author Zeynep Nursena KÜTÜK 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixLib.h"


float *returnVector(int size)
{
    float *newVector = (float *)malloc(size * sizeof(float)); //
    for (int i = 0; i < size; i++)
        newVector[i] = 0;

    return newVector;
}


float **returnMatrix(int row, int col)
{
    float **newMatrix = (float **)malloc(row * sizeof(float *));
    for (int i = 0; i < row; i++)
    {
        newMatrix[i] = (float *)malloc(col * sizeof(float));

        for (int j = 0; j < col; j++)
        {
            newMatrix[i][j] = 0;
        }
    }
    return newMatrix;
}



void freeMatrix(float **mat, int row)
{
    for (int i = 0; i < row; i++)
    {
        free((mat)[i]);
    }
    free(mat);
}



float mean(float *vec, int size)
{
    float sum = 0;
    float mean;
    for (int i = 0; i < size; i++)
    {
        sum += vec[i];
    }
    mean = sum / (float)size;
    return mean;
}



float *rowMeans(float **mat, int row, int col)
{
    int sum = 0;
    float mean;
    float *newMatris = returnVector(row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += mat[i][j];
        }

        newMatris[i] = sum / col;
        sum = 0;
    }
    return newMatris;
}



float *columnMeans(float **mat, int row, int col)
{
    float *newMatrix = returnVector(col);
    int sum = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            sum += mat[j][i];
        }

        newMatrix[i] = sum / row;

        sum = 0;
    }

    return newMatrix;
}



float standartDeviation(float *vec, int size)
{
    float sum = 0;
    float meanVec = mean(vec, size);
    for (int i = 0; i < size; i++)
    {
        sum += (pow((vec[i] - meanVec), 2));
    }
    return sqrt(sum / (float)size);
}



float covariance(float *vec1, float *vec2, int size)
{

    float vec1Mean = mean(vec1, size);
    float vec2Mean = mean(vec2, size);

    float sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += (*(vec1 + i) - vec1Mean) * (*(vec2 + i) - vec2Mean);
    }

    return sum / (float)size;
}



float correlation(float *vec1, float *vec2, int size)
{
   
    return covariance(vec1, vec2, size) / (standartDeviation(vec1, size) * standartDeviation(vec2, size));
}



float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{

    float **mat3 = returnMatrix(row1, col2);

    if (col1 != row2)
    {
        printf("Column of the first matrix is not same with another matrix");
        exit(0);
    }

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            int multiple = 0;
            for (int k = 0; k < col1; k++)
            {
                multiple += mat1[i][k] * mat2[k][j];
            }
            mat3[i][j] = multiple;
        }
    }

    return mat3;
}



float **matrixTranspose(float **mat, int row, int col)
{
    float **transposeMatrix = returnMatrix(col, row);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            transposeMatrix[j][i] = mat[i][j];
        }
    }
    return transposeMatrix;
}



float **covarianceMatrix(float **mat, int row, int col)
{
    {
        if (col = row)
        {
            float *columnMeanVec = columnMeans(mat, row, col);

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    mat[i][j] -= columnMeanVec[j];
                }
            }

            float **transpose = matrixTranspose(mat, row, col);
            float **covarianceMat = matrixMultiplication(transpose, mat, row, col, col, row);

            freeMatrix(transpose, row);
            free(columnMeanVec);

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    covarianceMat[i][j] /= row;
                }
            }

            return covarianceMat;
        }
        else
        {
            printf("Covariance matrix can not calculated.");
            return NULL;
        }
    }

}



float determinant(float **mat, int row)
{
    int determinant = 0;
    int determinantPlus = 0;
    int determinantMinus = 0;

    for (int i = 0; i < row; i++)
    {
        mat[i] = (float *)realloc(mat[i], 5 * sizeof(float));

        for (int j = 3; j < 5; j++)
        {
            mat[i][j] = mat[i][j - 3];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        determinantPlus += (mat[0][i] * mat[1][i + 1] * mat[2][i + 2]);
        determinantMinus += (mat[2][i] * mat[1][i + 1] * mat[0][i + 2]);
    }
    determinant = determinantPlus - determinantMinus;

    return determinant;
}


void printVector(float *vec, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%f\n", vec[i]);
    }
}



void printMatrix(float **mat, int row, int col)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%f ", (mat[i][j]));
        }
        printf("\n");
    }
}


void **randomMatrix(float **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = 1 + (rand() % 10);
        }
    }
}


void *randomVector(float *vector, int numberOfElements)
{
    for (int i = 0; i < numberOfElements; i++)
    {
        vector[i] = 1 + (rand() % 10);
    }
}
