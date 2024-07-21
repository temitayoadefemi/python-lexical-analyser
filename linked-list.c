#include <stdio.h>     // Standard input/output library (for printf, etc.)
#include <stdlib.h>    // Standard library (for malloc, free, etc.)
#include <stdbool.h>   // For boolean type
#include "linked-list.h"
#include "bst.h"

// Define the ListNode struct
void add_value(char* value) {
    ListNode* new_node = (ListNode*)malloc(sizeof(Node));
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        ListNode* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}


char* get_last_value() {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return NULL;
    }

    ListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current->value;
}
