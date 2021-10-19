#include <iostream>

using namespace std;


int matrix_size = 1000;

void fillMatrix(double** matrix)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            matrix[i][j] = (double)rand();
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

int main()
{
    cout << "Input matrix size: ";
    cin >> matrix_size;
    double** matrix1 = new double* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
    {
        matrix1[i] = new double[matrix_size];
    }
    fillMatrix(matrix1);
    printMatrix(matrix1);
    cout << endl;
    return main();
}


