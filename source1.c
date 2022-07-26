// Course: Advanced C programming
// exercise 1, question 1
// file name: ex1_q1.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// --------------------------- //


// --------------------------- //
// function declaration and main section:
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
    #include "ex1_q1.h"
#else
    #define FUNC_DECLARE
    unsigned long student_id();
    int * scanArray(int *);
    void printArray(int *, int);
    int arrangeArray(int **, int);

    int main()
    {
        unsigned long id_num;
        int *arr, n, k;

        // scan array:
        arr = scanArray(&n);

        // call functions:
        id_num = student_id();
        printf("[id: %lu] start main\n", id_num);

        k = arrangeArray(&arr, n);

        // write output:
        printf("Output:\n");
        printf("Size of k: %d\n", k);
        printf("Sorted array:\n");
        printArray(arr, n);
        free(arr);

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
    return 3135868689;
}
// --------------------------- //

// DO NOT CHANGE the following function:
int * scanArray(int *n)
{
    int i;
    int *arr;

    printf("Enter array size: ");
    scanf("%d", n);

    arr = (int*)malloc(sizeof(int) * (*n));
    for (i = 0; i < *n; ++i)
    {
        printf("Enter value #%d: ", i + 1);
        scanf("%d", arr+i);
    }

    return arr;
}
// --------------------------- //


// DO NOT CHANGE the following function:
void printArray(int *arr, int n)
{
    int i;
    printf("{");
    for (i = 0; i < n; ++i)
        printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
    printf("}\n");
}
// --------------------------- //

/// <summary>
/// Combine the two groups using realloc and memcpy only.
/// </summary>
/// <param>int **arr - Address of the array pointer</param>
///<param>int n - Size of the array</param>
/// <returns>Size of the first group</returns>
int arrangeArray(int **arr, int n)
{
    // your code:
    int low = 0, mid = 0, high = n - 1;
    int *arr_ptr = *arr;
    // If first element is smaller then last element, the array is sorted -> return n.
    if (arr_ptr[0] < arr_ptr[n-1]) {
        return n;
    }
    // Bin-searching - find the index where second array starts. mid == 'k'.
    while(low <= high) {
        mid = (high+low) / 2 + (high+low) % 2; // Round up mid.
        if (arr_ptr[mid - 1] >= arr_ptr[mid]) {
            // Found the index in which the second array starts (mid), so the size of first array = mid.
            break;
        }
        if (arr_ptr[0] > arr_ptr[mid]) {
            // mid is already within the second array, we need to back-up.
            high = mid - 1;
            continue;
        }
        low = mid + 1;
    }
    puts("\nSorting array");
    // Reallocate to get more memory for the sorting proccess, n + mid.
    arr_ptr = (int*)realloc(arr_ptr, (n+mid) * sizeof(int));
    // Copy 'first' array to the end. so we get, e.g: (a<b>c<d) --> (a<b>c<d<a<b)
    memcpy(arr_ptr+n ,arr_ptr, mid * sizeof(int));
    // Overwrite the array from array + k. --> (c<d<a<b,garb,garb)
    memcpy(arr_ptr ,arr_ptr + mid, n * sizeof(int));
    // Reallocate back to original size. so we get sorted array --> (c<d<a<b)
    arr_ptr = (int*)realloc(arr_ptr, n * sizeof(int));
    *arr = arr_ptr;
    return mid;
}

// --------------------------- //
