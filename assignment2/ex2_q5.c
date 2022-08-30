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
    printList(lst1);
    printList(lst2);

    // free list:
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
    return ;

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
    int lst1Size, lst2Size;

    // Getting length of lists, comparing lengths.
    lst1Size = circleListLength(*lst1);
    lst2Size = circleListLength(*lst2);

    /**
     ALGO PSEUDO
     Find first, and when found break the cycle
     For each list:
     - Iterate over the list
     - If current->data lesser than minAscii:
          set minAscii, and keep pointer to curr as (new) head
          Reset previous' next to NULL
     (Now we have two flat lists, we want to compare them)
     If the size is different -> return 0
     Iterate over each element in both lists in parallel,
          if matching, continue
          else, return 0
     return 1
     END ALGO PSEUDO
     */

    // In order to consolidate the code, push the list heads pointers to an array,
    // and loop over the array
    list **iter[] = {lst1, lst2};
    for (int i=0; i<2; i++) {
        if (!*(iter[i])) {
            continue;
        }
        list *curr, *head, *prev = NULL;
        // Setting all to *lst to support 1 letter case
        curr = head = *(iter[i]);
        int minAscii = curr->data-0;
        // Iterate until curr->next points to the (original) head, then curr is the last element.
        while (curr->next != *(iter[i])) {
            if (curr->next->data-0 < minAscii) {
                // Found lower ascii value, saving head as next and prev as current
                minAscii = curr->next->data-0;
                head = curr->next;
                prev = curr;
            }
            curr = curr->next;
        }
        // Setting prev to curr if it was never set inside the loop.
        prev = (prev) ? prev: curr;
        *(iter[i]) = head;
        // Break the list cycle
        prev->next = NULL;
    }

    // If sizes don't match, early return 0 (False)
    if (lst1Size != lst2Size) {
        return 0;
    }

    // sizes match - iterating over data and comparing, returning 0 as soon as a mismatch is found
    list * tempHead1 = *lst1;
    list * tempHead2 = *lst2;
    while(lst1Size--) {
        if (tempHead1->data != tempHead2->data) {
            return 0;
        }
        tempHead2 = tempHead2->next;
        tempHead1 = tempHead1->next;
    }

    return 1;
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
    if (!lst) {
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
