#include <stdio.h>     // Standard input/output library (for printf, etc.)
#include <stdlib.h>    // Standard library (for malloc, free, etc.)
#include <stdbool.h>   // For boolean type
#include "linked-list.h"

// Define the ListNode struct
typedef struct ListNode {
    int key;
    int value;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;


// Define the LinkedList struct
typedef struct LinkedList {
    struct ListNode *head;
} LinkedList;


// Function to create a new node
ListNode* create_node(int key, int value) {
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Function to insert a new node into the linked list
void insert(ListNode *node, LinkedList *linkedlist, bool singly) {
    if (linkedlist->head == NULL) {
        linkedlist->head = node;
        node->next = NULL;
    } else {
        ListNode *current = linkedlist->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
        if (!singly) {
            node->prev = current;
        }
        node->next = NULL;
    }
}

// Function to delete a node from the linked list by key
void delete_node(int key, LinkedList *linkedlist, bool singly) {
    if (linkedlist->head == NULL) {
        return;
    }

    ListNode *current = linkedlist->head;
    ListNode *previous = NULL;

    if (current != NULL && current->key == key) {
        linkedlist->head = current->next;
        if (!singly && current->next != NULL) {
            current->next->prev = NULL;
        }
        free(current);
        return;
    }

    while (current != NULL && current->key != key) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (!singly && current->next != NULL) {
        current->next->prev = previous;
    }
    previous->next = current->next;
    free(current);
}

// Function to find and return a node by key
ListNode* search(int key, LinkedList *linkedlist) {
    ListNode *current = linkedlist->head;
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to replace a node by key
void replace(int key, ListNode *node, LinkedList *linkedlist, bool singly) {
    ListNode *current = linkedlist->head;
    ListNode *previous = NULL;

    while (current != NULL && current->key != key) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (previous == NULL) {
        linkedlist->head = node;
    } else {
        previous->next = node;
    }

    node->next = current->next;
    if (!singly) {
        node->prev = previous;
        if (current->next != NULL) {
            current->next->prev = node;
        }
    }

    free(current);
}

// Function to edit a node's value by key
void edit(int key, int value, LinkedList *linkedlist) {
    ListNode *current = linkedlist->head;
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
}

// Function to reverse a linked list
void reverse(LinkedList *linkedlist, bool singly) {
    ListNode *current = linkedlist->head;
    ListNode *previous = NULL;
    ListNode *nextnode = NULL;

    while (current != NULL) {
        nextnode = current->next;
        current->next = previous;
        if (!singly && previous != NULL) {
            previous->prev = current;
        }
        previous = current;
        current = nextnode;
    }

    linkedlist->head = previous;
    if (!singly && previous != NULL) {
        previous->prev = NULL;
    }
}

// Function to split a linked list into two parts at a given index
void split(LinkedList *linkedlist, int index, ListNode **head1, ListNode **head2) {
    if (!linkedlist || !linkedlist->head) {
        *head1 = NULL;
        *head2 = NULL;
        return;
    }

    ListNode *current = linkedlist->head;
    ListNode *previous = NULL;
    int count = 0;

    while (current != NULL && count < index) {
        previous = current;
        current = current->next;
        count++;
    }

    *head1 = linkedlist->head;
    *head2 = current;

    if (previous) {
        previous->next = NULL;
    }

    if (index == 0) {
        *head1 = NULL;
    }
}

// Function to find and return the middle node of a linked list
ListNode* get_middle(LinkedList *linkedlist) {
    ListNode *slow = linkedlist->head;
    ListNode *fast = linkedlist->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to merge two linked lists
ListNode* merge(ListNode *a, ListNode *b, bool key) {
    ListNode *result = NULL;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (key) {
        if (a->key <= b->key) {
            result = a;
            result->next = merge(a->next, b, key);
        } else {
            result = b;
            result->next = merge(a, b->next, key);
        }
    } else {
        if (a->value <= b->value) {
            result = a;
            result->next = merge(a->next, b, key);
        } else {
            result = b;
            result->next = merge(a, b->next, key);
        }
    }

    return result;
}

// Function to sort a linked list
ListNode* sort(ListNode *head, bool key) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode *middle = get_middle(head);
    ListNode *next_to_middle = middle->next;

    middle->next = NULL;

    ListNode *left = sort(head, key);
    ListNode *right = sort(next_to_middle, key);

    ListNode *result = merge(left, right, key);

    return result;
}

// Function to print the linked list
void print_list(LinkedList *linkedlist) {
    ListNode *current = linkedlist->head;
    while (current != NULL) {
        printf("Key: %d, Value: %d\n", current->key, current->value);
        current = current->next;
    }
}