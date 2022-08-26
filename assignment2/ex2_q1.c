// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q1.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
    int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
fraction ** createMatrix(int rows, int cols);
fraction ** matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction** B, int rows, int cols);
void freeMatrix(fraction** B, int rows);
/** DECLARE HERE ONE FUNCTION ACCORDING TO YOUR NEEDS **/
int getGreatestCommonDivisor(int first, int second);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
    unsigned long id_num;
    fraction** B;
    int A[ROWS][COLS] = {
        {5, 12, 6, 8},
        {4, 7, 0, 9},
        {13, 20, 8, 2},
        {18, 0, 2, 6}
    };

    // call functions:
    id_num = student_id();
    printf("[id: %lu] start main\n", id_num);

    B = matrixAverageNeighbor(A, ROWS, COLS);

    // write output:
    printf("Output:\n");
    printMatrix(B, ROWS, COLS);

    // free matrix:
    freeMatrix(B, ROWS);

    return 0;
}
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
    // return your id number,
    // for example if your id is 595207432
    // return 595207432;
    // your code:
    return 313586869;

}
// --------------------------- //


/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>

    // your code:
int getGreatestCommonDivisor(int first, int second) {
    if(second) {
        return getGreatestCommonDivisor(second, first % second);
    }
    return first;
}

// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction** createMatrix(int rows, int cols)
{
    // your code:
    fraction **matrix = (fraction**)malloc(rows * sizeof(fraction));
    for (int i = 0; i < rows; i++)
        matrix[i] = (fraction*)malloc(cols * sizeof(fraction));

    return matrix;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix
/// and for each cell in the matrix calculates
/// the average of its neighbors.
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
    // your code:
    fraction **matrix = createMatrix(rows, cols);
    for (int i = 0 ; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("i: %d, j: %d", i, j);
            matrix[i][j] = neighborFractionAverage(A,i,j,rows,cols);
            printf("\nFRACTION STRUCT IS: %d %d/%d\n", matrix[i][j].num, matrix[i][j].numerator, matrix[i][j].denominator);
        }
    }
    return matrix;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
    // your code:
    struct fraction avgFraction = *(fraction *)malloc(sizeof(fraction));
    int sum = 0, gcd, divisor = 0;
    int offseti[] = {-1, -1, -1, 0, 0, 1, 1, 1 };
    int offsetj[] = {-1, 0, 1, -1, 1, -1, 0, 1 };
    printf("\nCalculating offsets for A[%d][%d] - (%d) \n" ,i, j, A[i][j]);
    for (int n = 0; n < 8; n++) {
        int neighbouri = i + offseti[n];
        int neighbourj = j + offsetj[n];
        if (neighbouri < 0 || neighbouri >= rows || neighbourj < 0 || neighbourj >= cols) {
            continue;
        }
        divisor++;
        printf("ADDING A[%d][%d] = %d\n", neighbouri, neighbourj, A[neighbouri][neighbourj]);
        sum += A[neighbouri][neighbourj];
    }
    gcd = getGreatestCommonDivisor(sum, divisor);
    avgFraction.denominator = divisor/gcd;
    avgFraction.numerator = (sum%divisor)/gcd;
    avgFraction.num = (int)(sum/divisor);

    return avgFraction;
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction** B, int rows, int cols)
{
    // your code:
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            printf("%d %d/%d, ", B[i][j].num, B[i][j].numerator, B[i][j].denominator);
        }
        puts("\n");
    }
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction** B, int rows)
{
    // your code:
    for (int i = 0; i < rows; i++) {
        free(B[i]);
    }
    free(B);
}
// --------------------------- //
