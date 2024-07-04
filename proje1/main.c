/*
 * @file matrixLib.c
 * @description MatrixLib.c dosyasında oluşturulmuş fonksiyonların testinin yapıldığı dosya
 * @author Zeynep Nursena KÜTÜK 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrixLib.h"

int main(int number, char *args[])
{

    if (number < 2)
    {
        printf("\nThe number of arguments is not enough.\n");
        return 0;
    }

    srand(atoi(args[1]));

    printf("\nFirst Matrix\n");
    float **mat = returnMatrix(3, 3);
    randomMatrix(mat, 3, 3);
    printMatrix(mat, 3, 3);

    printf("\n****************************\n");

    printf("\nRow Means\n");
    float *rowVec = rowMeans(mat, 3, 3);
    printVector(rowVec, 3);

    printf("\n****************************\n");

    printf("\nCol Means\n");
    float *colVec = columnMeans(mat, 3, 3);
    printVector(colVec, 3);

    printf("\n****************************\n");

    printf("\nTranspose Matrix\n");
    float **trans = matrixTranspose(mat, 3, 3);
    printMatrix(trans, 3, 3);
    freeMatrix(mat, 3);
    free(rowVec);
    free(colVec);

    printf("\n****************************\n");

    printf("\nSecond Matrix\n");
    float **mat2 = returnMatrix(2, 2);
    randomMatrix(mat2, 2, 2);
    printMatrix(mat2, 2, 2);

    printf("\n****************************\n");

    printf("\n\nThird Matrix\n");
    float **mat3 = returnMatrix(2, 2);
    randomMatrix(mat3, 2, 2);
    printMatrix(mat3, 2, 2);

    printf("\n****************************\n");

    printf("\nMultiplication Matrix\n");
    float **multi = matrixMultiplication(mat2, mat3, 2, 2, 2, 2);
    printMatrix(multi, 2, 2);
    freeMatrix(mat2, 2);
    freeMatrix(mat3, 2);
    freeMatrix(multi, 2);

    printf("\n****************************\n");

    printf("\nFourth Matrix\n");
    float **mat4 = returnMatrix(3, 3);
    randomMatrix(mat4, 3, 3);
    printMatrix(mat4, 3, 3);

    printf("\n****************************\n");

    printf("\nDeterminant of  Matrix\n");
    float det = determinant(mat4, 3);
    printf("\n%f\n", det);
    freeMatrix(mat4, 3);

    printf("\n****************************\n");

    printf("\nFirst Vector\n");
    float *vec1 = returnVector(3);
    randomVector(vec1, 3);
    printVector(vec1, 3);

    printf("\n****************************\n");

    printf("\nMean of Vectors\n");
    float mean1 = mean(vec1, 3);
    printf("\n%f\n", mean1);

    printf("\n****************************\n");

    printf("\nSecond Vector\n");
    float *vec2 = returnVector(3);
    randomVector(vec2, 3);
    printVector(vec2, 3);

    printf("\n****************************\n");

    printf("\nVector Covariance\n");
    float covar = covariance(vec1, vec2, 2);
    printf("%f\n", covar);

    printf("\n****************************\n");

    printf("\nVector Correlation\n");
    float correl = correlation(vec1, vec2, 2);
    printf("%f\n", correl);
    free(vec1);
    free(vec2);

    printf("\n****************************\n");

    printf("\nFifth Matrix\n");
    float **mat5 = returnMatrix(3, 3);
    randomMatrix(mat5, 3, 3);
    printMatrix(mat5, 3, 3);

    printf("\n****************************\n");

    printf("\nCovariance Matrix\n");
    float **covarianceM = covarianceMatrix(mat5, 3, 3);
    printMatrix(covarianceM, 3, 3);

    printf("\n****************************\n");

    printf("\nFree Covariance Matrix\n");
    freeMatrix(covarianceM, 3);
    printMatrix(covarianceM, 3, 3);

    printf("\n****************************\n");

    printf("\nFree Fifth Matrix\n");
    freeMatrix(mat5, 3);
    printMatrix(mat5, 3, 3);
    return 0;
}
