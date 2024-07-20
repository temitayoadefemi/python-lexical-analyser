#include <stdio.h>     // Standard input/output library (for printf, etc.)
#include <stdlib.h>    // Standard library (for malloc, free, etc.)


typedef struct ListNode {

    int key;
    int value;
    struct ListNode *next;
    struct ListNode *prev;


} ListNode;

typedef struct LinkedList {
    struct ListNode *head;

} LinkedList;