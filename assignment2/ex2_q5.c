// Course: Advanced C programming
// exercise 2, question 5
// file name: ex2_q5.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q5.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct list
{
    char data;
    struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
list* createElement(char data, list* next);
list* createCircleListFromString(char* str);
int compareCircleLists(list** lst1, list** lst2);
int circleListLength(list *lst);
void printList(list* lst);
void freeList(list** lst);

// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
    unsigned long id_num;
    int result;
    list* lst1 = NULL, *lst2 = NULL;
    char str1[] = "duezax";
    char str2[] = "zaxdue";
    // call functions:
    id_num = student_id();
    printf("[id: %lu] start main\n", id_num);
    lst1 = createCircleListFromString(str1);
    lst2 = createCircleListFromString(str2);

    // write output:
    printf("Output:\n");
    result = compareCircleLists(&lst1, &lst2);
    printf("RESULTS: %d\n", result);

    printList(lst1);
    printList(lst2);

//    // free list:
    freeList(&lst1);
    freeList(&lst2);

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


///// <summary>
///// The function receives a value from type int,
//// and the pointer to the next element in list
///// and returns a dynamic element from type list
///// </summary>
///// <param>char data - value from type char, the value of the element</param>
///// <param>list* next - pointer to the next value after the newly created element</param>
///// <returns>dynamic value from type list</returns>
list* createElement(char data, list* next)
{
    list* item = (list*)(malloc(sizeof(list)));
    item->data = data;
    item->next = next;
    return item;
}
// --------------------------- //

/// <summary>
/// The function receives a string array
/// and returns a newly created list
/// </summary>
/// <param>char* str - The array string</param>
/// <returns>newly created list</returns>
list* createCircleListFromString(char* str)
{
    list* head = NULL;
    list* tail = NULL;
    while (*str != '\0')
    {
        if (!head)
            head = tail = createElement((*str++), NULL);
        else
        {
            tail->next = createElement((*str++), NULL);
            tail = tail->next;
        }
    }
    if (tail)
        tail->next = head;
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
        printf("%c%s", lst->data, (lst->next) ? "--> ": "\n");
        lst = lst->next;
    }
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list
/// set first element to be the pivot and split all elements in lst to small and big accordingly
/// </summary>
/// <param>list** lst1 - Pointer to the pointer of the head of the 1st circle list</param>
/// <param>list** lst2 - Pointer to the pointer of the head of the 2nd circle list</param>
/// <returns>true if both lists are circly equal</returns>
int compareCircleLists(list** lst1, list** lst2)
{
    // your code:
    int lst1Size, lst2Size, rv;

    // Getting length of lists, comparing lengths.
    lst1Size = circleListLength(*lst1);
    lst2Size = circleListLength(*lst2);
    rv = (lst1Size != lst2Size) ? 0: 1;

    // If both lists are empty, no need to "break circles" --> returns rv
    if (lst2Size == 0 && lst1Size == 0) {
        return rv;
    }

    if (*lst1) {
        list *curr, *head, *prev;
        // Setting all to *lst to support 1 letter case
        curr = head = prev = *lst1;
        int minAscii = curr->data-0;
        for (int i = 0; i < lst1Size; i++) {
            if (curr->next->data-0 < minAscii) {
                // Found lower ascii value, saving head as next and prev as current
                minAscii = curr->next->data-0;
                head = curr->next;
                prev = curr;
            }
            curr = curr->next;
        }
        *lst1 = head;
        prev->next = NULL;
    }

    /**
     * DUPLICATE CODE --> BETTER FUNCTION THIS SHIT
     */

    if (*lst2) {
        list *curr2, *head2, *prev2;
        // Setting all to *lst to support 1 letter case
        curr2 = head2 = prev2 = *lst2;
        int minAscii2 = curr2->data-0;
        for (int j = 0; j < lst2Size; j++) {
            if (curr2->next->data-0 < minAscii2) {
                // Found lower ascii value, saving head as next and prev as current
                minAscii2 = curr2->next->data-0;
                head2 = curr2->next;
                prev2 = curr2;
            }
            curr2 = curr2->next;
        }
        *lst2 = head2;
        prev2->next = NULL;
    }
    /**
     * END OF DUPLICATE
     */

    // If size matches, iterating over data and comparing
    if (rv) {
        for (int m = 0; m < lst1Size; m++) {
            if ((*lst1)->data != (*lst2)->data) {
                // Set rv --> 0 and breaks if there is a miss-match
                rv = 0;
                break;
            }
        }
    }

    return rv;
}

// --------------------------- //


/// <summary>
/// The function receives a pointer to the circle linked list,
/// and returns how many elements inside.
/// </summary>
/// <param>list* lst - Pointer to an element inside the list</param>
/// <returns>amount of elements in the circle list</returns>
int circleListLength(list* lst)
{
    // your code:
    if (!(lst)) {
        return 0;
    }
    // At least 1 item.
    int cnt = 1;
    // Marking first item's data.
    char first = lst->data;
    while(first != lst->next->data) {
        // Increasing cnt & progressing list until we complete cycle
        cnt++;
        lst = lst->next;
    }
    return cnt;
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
