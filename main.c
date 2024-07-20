#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h> 
#include "bst.c"



typedef enum {
  _KEYWORD_,
  _SEPERATOR_,
  _VALUE_,
} TYPE;


typedef enum {
   _FOR_,
   _IN_,
} KEYWORD;


typedef enum {
    _EQUALS_,
} SEPERATOR;


typedef enum {
    _INT_,
    _FLOAT_,
    _STRING_,
} VALUE;


typedef struct {
    TYPE token_type;
    VALUE token_value;
} TOKEN;


typedef struct Node {
    char* value;
    struct Node* next;
} Node;

Node* head = NULL;


void add_value(char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        Node* current = head;
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

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current->value;
}


#include <stdio.h>
#include <ctype.h> // Required for isalnum and isalpha functions

int main() {
    FILE *file;
    char line[256];

    // Open the file
    file = fopen("file.py", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        char value[256];
        int valueIndex = 0;
        int capturing_value = 0; // Flag to start capturing the value after '='
        int captured = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            // Handling character by character
            if (line[i] == '=') {
                if (valueIndex > 0) {
                    value[valueIndex] = '\0';
                    printf("Alphabetic sequence: %s\n", value);
                    valueIndex = 0;
                }
                capturing_value = 1; // Set flag to start capturing after '='
                continue; // Move to the next character to skip '='
            }

            if (capturing_value) {
                // Capture values after '='
                if (isalnum(line[i]) || line[i] == '_') { // Accept underscore as part of variable names
                    value[valueIndex++] = line[i];
                } else {
                    if (valueIndex > 0) {
                        value[valueIndex] = '\0'; // Null-terminate the string
                        printf("Value after '=': %s\n", value);
                        valueIndex = 0;
                        capturing_value = 0; // Stop capturing after a complete value
                        captured = 1;
                        char key;
                        key = get_last_value();
                        Node *node
                        
                    }
                }
            } else {
                // Capture alphabetic sequences
                if (isalpha(line[i])) {
                    value[valueIndex++] = line[i];
                } else {
                    if (valueIndex > 0) {
                        value[valueIndex] = '\0'; // Null-terminate the string
                        printf("Alphabetic sequence: %s\n", value);
                        if (value != "for" && value != "in" && value != "print"){
                            add_value(value);
                            printf("Added Value");
                        } 
                        valueIndex = 0;
                    }
                }
            }
        }

        // Final check at the end of the line
        if (valueIndex > 0) {
            value[valueIndex] = '\0';
            if (capturing_value) {
                printf("Value after '=': %s\n", value);
            } else {
                printf("Alphabetic sequence: %s\n", value);
            }
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
