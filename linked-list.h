#include <stdio.h>     // Standard input/output library (for printf, etc.)
#include <stdlib.h>    // Standard library (for malloc, free, etc.)

typedef struct ListNode {
    char* value;
    struct ListNode* next;
} ListNode;

ListNode* head = NULL;
