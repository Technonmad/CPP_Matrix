#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;


int matrix_size = 1000;

void fillMatrix(double** matrix)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            matrix[i][j] = (double)(rand() / 100);
        }
    }
}

void printMatrix(double** matrix)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void MultiplyMatrix(double** matrixOne, double** matrixTwo, double** resultMatrix)
{

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            for (int k = 0; k < matrix_size; k++)
            {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
}

void ParallelMultiplyMatrix(double** matrixOne, double** matrixTwo, double** resultMatrix)
{
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            for (int k = 0; k < matrix_size; k++)
            {
                resultMatrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
}

double shpoor(double** matrix)
{
    double result = 0;
    for (int i = 0; i < matrix_size; i++)
    {
        result += matrix[i][i];
    }

    return result;
}

int main()
{
    cout << "********************************************************************" << endl;
    cout << "Input matrix size: ";
    cin >> matrix_size;

    double** matrix1 = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
    {
        matrix1[i] = new double[matrix_size];
    }

    double** matrix2 = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
    {
        matrix2[i] = new double[matrix_size];
    }

    double** resultMatrix = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
    {
        resultMatrix[i] = new double[matrix_size];
    }

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            resultMatrix[i][j] = 0;
        }
    }
    
    fillMatrix(matrix1);
    fillMatrix(matrix2);

    if (matrix_size <= 5) {
        printMatrix(matrix1);
        cout << endl;

        printMatrix(matrix2);
        cout << endl;
    }

    auto start1 = chrono::high_resolution_clock::now();
    MultiplyMatrix(matrix1, matrix2, resultMatrix);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed_time = end1 - start1;
    cout << "One thread:" << endl;
    cout << "\tElapsed time: " << elapsed_time.count() << endl;

    if (matrix_size <= 5) printMatrix(resultMatrix);
    else cout << "Shpoor: " << (long)shpoor(resultMatrix) << endl;

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            resultMatrix[i][j] = 0;
        }
    }

    auto start2 = chrono::high_resolution_clock::now();
    ParallelMultiplyMatrix(matrix1, matrix2, resultMatrix);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<float> elapsed_time2 = end2 - start2;
    cout << "4 threads:" << endl;
    cout << "\tElapsed time: " << elapsed_time2.count() << endl;

    if (matrix_size <= 5) printMatrix(resultMatrix);
    else cout << "Shpoor: " << (long)shpoor(resultMatrix) << endl;
    cout << endl;

    return main();
}


