// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q4.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q4.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define SIZE(a) (sizeof(a) / sizeof((a)[0]))
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct list
{
    int data;
    struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
list* createElement(int data, list* next);
list* createListFromArray(int* arr, int n);
void printList(list* lst);
void partition(list** lst, list** pivot, list** small, list** big);
void quickSortList(list** lst);
void freeList(list** lst);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
    unsigned long id_num;
    int n;
    list* lst = NULL;
    int arr[] = { 5, 3, 7, 1, 9, 8, 2, 5, 6 };

    // call functions:
    id_num = student_id();
    printf("[id: %lu] start main\n", id_num);
    lst = createListFromArray(arr, SIZE(arr));
    quickSortList(&lst);

    // write output:
    printf("Output:\n");
    printList(lst);

    // free list:
    freeList(&lst);

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
    return 316517390;
}
// --------------------------- //


///// <summary>
///// The function receives a value from type int,
//// and the pointer to the next element in list
///// and returns a dynamic element from type list
///// </summary>
///// <param>int data - value from type int, the value of the element</param>
///// <param>list* next - pointer to the next value after the newly created element</param>
///// <returns>dynamic value from type list</returns>
list* createElement(int data, list* next)
{
    list* item = (list*)(malloc(sizeof(list)));
    item->data = data;
    item->next = next;
    return item;
}
// --------------------------- //

/// <summary>
/// The function receives an integer array and its size
/// and returns a newly created list
/// </summary>
/// <param>int* arr - The array</param>
/// <param>int n - Amount of elements in array</param>
/// <returns>newly created list</returns>
list* createListFromArray(int* arr, int n)
{
    int i;
    list* head = NULL;
    for (i = n - 1; i >= 0; i--)
        head = createElement(arr[i], head);
    return head;
}
// --------------------------- //


/// <summary>
/// The function receives a list,
/// and print its values.
/// </summary>
/// <param>list* lst - the list</param>
/// <returns>None</returns>
void printList(list* lst)
{
    // your code:
    while (lst) {
        printf("%d%s", lst->data, (lst->next) ? ", ": "\n");
        lst = lst->next;
    }
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list
/// set first element to be the pivot and split all elements in lst to small and big accordingly
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>list** pivot - Pointer to the pointer of the new pivot</param>
/// <param>list** small - Pointer to the pointer of the head of the small elements</param>
/// <param>list** big - Pointer to the pointer of the head of the big elements</param>
/// <returns>None</returns>
void partition(list** lst, list** pivot, list** small, list** big)
{
    // your code:
    if (!(*lst)) {
        return;
    }
    // Pivot needs to point to the list head, and then be detached from the list
    *pivot = *lst;
    // Remove pivot from the list
    *lst = (*pivot)->next;
    // Detach by unset 'next'
    (*pivot)->next = NULL;

    list *tmp = NULL; // Used for swapping
    // 'operate' is a dynamically set pointer to a list's head.
    // the value will be set according to the currently tested node's value
    // compared to the pivot.
    // Then a consolidated operation would be performed on the correct list.
    list **operate = NULL;
    while (*lst) {
        operate = small; // Default option
        if ((*lst)->data > (*pivot)->data) {
            // current node is greater than pivot:
            operate = big;
        }
        tmp = (*lst);
        (*lst) = (*lst)->next;
        tmp->next = (*operate);
        (*operate) = tmp;
    }
    if (*lst != NULL) {
        return;
    }
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list
/// and sort all elements by the quickSort method.
/// It is advisable to go over the standard implementation of quicksort on an array
/// </summary>
/// <param>list* curr - Pointer to an element inside the list</param>
/// <returns>None</returns>
void quickSortList(list** lst)
{
    // your code:
    list *pivot = NULL;
    list *small = NULL;
    list *big = NULL;
    if (!(*lst)) {
        return;
    }
    partition(lst, &pivot, &small, &big);
    quickSortList(&small);
    quickSortList(&big);

    // By default, set pivot as lst's head (might be overriden later)
    *lst = pivot;
    if (small) {
        // Small list is populated, so need to:
        // - Set small's head as lst's head
        // - Connect small's tail and pivot
        *lst = small;

        // get to the end of 'small', and append pivot
        list* tmp = small;
        while (tmp) {
            if (!tmp->next) {
                tmp->next = pivot;
                break;
            }
            tmp = tmp->next;
        }
    }
    // Connect pivot to 'big' list. No worries if big is NULL
    pivot->next = big;

    // At this point (*lst) is pointing at either:
    // - pivot as a single node (if list was single node)
    // - pivot, connected to the big's head if it was populated
    // - small's head, connected to pivot, and potentially big's head
}
// --------------------------- //


/// <summary>
/// The function free all allocated memory of a list.
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <returns>None</returns>
void freeList(list** lst)
{
    // your code:
    list *tmp;
    while (*lst) {
        tmp = *lst; // Keep ptr for deletion
        *lst = (*lst)->next; // Advance in the list
        free(tmp); // Free saved ptr
    }
}
// --------------------------- //
