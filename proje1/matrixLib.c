/*
 * @file matrixLib.c
 * @description Matrix fonksiyonlarının gövdelerinin bulunduğu dosya
 * @assignment Birinci proje ödevi
 * @date 05.12.2022
 * @author Zeynep Nursena KÜTÜK - zeynepnursena.kutuk@stu.fsm.edu.tr
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixLib.h"

/*
Parametre olarak aldığı size miktarı kadar heap'te rastgele alan oluşturan metod.
bu metotta calloc ile alan oluşturmak yerine önce malloc ile rastgele değerler içeren alan oluşturup
daha sonra for döngüsü ile gezerek bu rastgele değerleri 0 ile doldurdum.
*/

float *returnVector(int size)
{
    float *newVector = (float *)malloc(size * sizeof(float)); //
    for (int i = 0; i < size; i++)
        newVector[i] = 0;

    return newVector;
}

/*
Parametre olarak aldığı row ve col kadar miktarı kadar heap'te rastgele değerler içeren matris oluşturan metod.
bu metotta calloc ile matris oluşturmak yerine önce malloc ile rastgele değerler içeren matris oluşturup
daha sonra for döngüsü ile gezerek bu rastgele değerlerin içini kendim 0 ile doldurdum.
*/

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

/*
Eğer bir matrisi bir daha çağırmayacağımızdan eminsek freeler, heapteki alanı boşaltırız.
Dinamik olarak oluşturmuş olduğum matrisleri, işim bittikten sonra heapten geri iade etmek için freeMatrix metodunu oluşturdum.
Bu vektörün her elemanı matrisin bir satırını taşıyordu, şimdi boş bir vektör oldu.
Bu boş vektörü de iade etmek için for döngümün dışında tekrar free(mat) kullandım.
Burada for kullandıktan sonra eğer tekrar free(mat) yapmasaydım elimde boş bir vektör kalmış olacaktı.
*/

void freeMatrix(float **mat, int row)
{
    for (int i = 0; i < row; i++)
    {
        free((mat)[i]);
    }
    free(mat);
}

/*
Parametre olarak verilen vektörün aritmetik ortalamasını bulan metot.
Bildiğimiz aritmetik ortalama formülünü kullandım.
For döngüsü ile vec'in her bir elemanını gezip toplama eşitleyip,
sonrasında eleman sayıma yani parametre olarak verdiğim size a bölerek ortalamayı buldum.
Son olarak bulduğum bu mean i return ile döndürdüm.
Int tipinde vermiş olduğum size'ı float'a cast ettim ki program sırasında bana sıkıntı yaratmasın.
*/

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

/*
Verilen bir matrisin satırlarının ortalamasını bulan metot.
İlk olarak daha önce oluşturmuş olduğum returnVector metodu ile yeni bir vektör oluşturdum.
Bu vektör benim matrisimdeki satırların ortalamasını tutacak.
For döngümle matrisimin satırlarından başlayarak, sütunlarını gezip o satır ve sütundaki sayıları toplama eşitleyip,
sütuna bölerek satır ortalamasını buldum.
Bulduğum bu ortalamayı yeni oluşturduğum matrisin elemanlarına atadım.
Toplamı tekrar 0 a eşitledim. Çünkü yeni satıra geldiğinde farklı bir eleman için işlem yapıyor olması gerekiyor.
Son olarak da return ile yeni matrisi döndürdüm.
*/

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

/*
Verilen bir matrisin sütunlarının ortalamasını bulan metot.
İlk olarak daha önce oluşturmuş olduğum returnVector metodu ile yeni bir vektör oluşturdum.
Bu vektör benim matrisimdeki sütunların ortalamasını tutacak.
For döngümle matrisimin sütunlarından başlayarak, satırlarını gezip o satır ve sütundaki sayıları toplama eşitledim.
Daha sonra yeni oluşturduğum matrisin elemanına bu bulduğum toplamı satıra bölerek bulduğum değeri yani ortalamayı atadım.
Toplamı tekrar 0 a eşitledim. Çünkü yeni satıra geldiğinde farklı bir eleman için işlem yapıyor olması gerekiyor.
Son olarak da return ile yeni matrisi döndürdüm.
*/

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

/*
İlk olarak parametre olarak verdiğim vektörde yer alan elemanların aritmetik ortalamasının alınması gerekmektedir.
Bunu da daha önce oluşturmuş olduğum mean metodu ile yaptım.
Her bir elemanın, bulunan aritmetik ortalama değerinden farkını hesaplayıp, bulunan bu farkların da karesi hesapladım.
Bulunan farkların karelerinin hepsini toplayıp toplama eşitledim.
Ve son olarak size'a bölüp, bulduğum sonucun da karekökünü alarak standart sapmayı hesapladım.
*/

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

/*
Öncelikle parametre olarak verilen iki vektörün de ortalamasını daha önce oluşturduğum metot ile buldum.
For döngümle size kadar gezerek her iki vektörün de o anki elemanından vektörün ortalamasını çıkararak,
bu çıkan iki sonucu da birbiri ile çarparak her seferinde bu çarpımı sum'a ekleyerek sum'ı buldum.
Döngüm sonlandığında return ile bu toplamı size a bölerek kovaryansı bulup, bulduğum değeri döndürmüş oldum.
*/

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

/*
korelasyon = kovaryans / (standart sapma çarpımı (verilen iki vektör))
*/

float correlation(float *vec1, float *vec2, int size)
{
    /*
    float correlation = covariance(vec1, vec2, size) / (standartDeviation(vec1, size) * standartDeviation(vec2, size));
    return correlation;
    */

    return covariance(vec1, vec2, size) / (standartDeviation(vec1, size) * standartDeviation(vec2, size));
}

/*Matris çarpım kuralını dikkate alarak oluşturduğum çarpım metodu.
İki matrisi çarpabilmemiz için verilen birinci matrisin sütun sayısı = ikinci matrisin sütun sayısına eşit olmalıdır.
If ile bunun kontrolünü yaptım. Eşit ise alt satıra geçip çarpım işlemlerini yapmasını sağladım.
*/

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

/*
Parametre olarak verilen matrisin satır ve sütunlarının yerlerini değiştirilmesiyle oluşacak olan transpoz matrisi oluşturduğum metot.
*/

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

/*
Kovaryans matrisin hesaplanması için satır ve sütun sayısı eşit olmalı.
Bunun kontrolünü if else yapısıyla yaptım.
Eğer satır=sütun ise kodlarım çalışacak ve covarianceMatrix imi return edecek.
satır!=sütun ise ekrana hesaplanamaz yazdırıp, null döndürecek.
Öncelikle columnMeans ile sütundaki elemanların ortalamalarının bulunmasıyla oluşan vektörü buldum.
For döngüsü ile parametre olarak girdiğim matrisin satır ve sütunlarını gezip, gezdiğim elemanı kendisinden o sütundaki ortalamayı çıkararak
yine o matrise eşitledim.
Daha önce oluşturmuş olduğum matrixTranspose ve matrixMultiplication ile işlemler yaparak,
transpose matris oluşturup bu oluşturduğum matrisle de covarianceMatris hesabını yapmaya başladım.
covarianceMatrix = transpose matris ile parametre olarak verilen matrisin çarpımının elemanlarının her birinin satır sayısına bölünmesi ile bulunuyor.
Son olarak da bulduğum covarianceMat i return ettim..
*/

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

    /*float **matrix = returnMatrix(row, col);
     float **transposeMatrix = matrixTranspose(mat, row, col);

     for (int i = 0; i < row; i++)
     {
         for (int j = 0; j < col; j++)
         {
             matrix[i][j] = covariance(transposeMatrix[i], transposeMatrix[j], row);
         }
     }
     return matrix;
    */
}

/*
Determinant hesabını sarrus yöntemi ile yaptım.
Sarrus ile hesaplarken sütun eklemesi yapıyoruz.
i+2 ile de bu işlemi yapabilirdik ama ben direkt 5 yazarak yapmayı tercih ettim.
Zaten sarrus yöntemi sadece 3*3 lük matrisler için kullanılan bir yol.
For döngüm içerisinde realloc ile dinamik olarak diziyi genişletmiş oldum.
İç içe for döngüsünü kullanarak içteki for döngümde de j'yi üçten başlatarak matrisin ilk iki sütununu son iki sütuna eşitledim.
böylelikle 5*5 lik matris oluşmuş oldu.
Çarpraz olarak çarpım işlemlerini yapıp birbirinden çıkartarak determinantı buldum.
Son olarak bulduğum determinant değerini return ettim.
*/

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

// Verilen vektörü ekrana yazdırmak için kullandığım metot

void printVector(float *vec, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%f\n", vec[i]);
    }
}

// Verilen matrisi ekrana yazdırmak için kullandığım metot

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

// Mainde oluşturduğum metotları denerken kullanacağım matrislerin içini random olarak doldurduğum metot
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

// Mainde oluşturduğum metotları denerken kullanacağım vektörlerin içini random olarak doldurduğum metot
void *randomVector(float *vector, int numberOfElements)
{
    for (int i = 0; i < numberOfElements; i++)
    {
        vector[i] = 1 + (rand() % 10);
    }
}
