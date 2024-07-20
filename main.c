#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bst.h"
#include "linked-list.h"




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



int check_for_unique(char value){
    if (value == "for") {
        return 0;
    }
    else if (value == "in") {
        return 0;
    }

    return 1;
}


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
        // Loop through each character in the line
        char value[256];
        int valueIndex = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            // Print each character
            printf("Character: %c\n", line[i]);

            // If the character is alphabetic, append it to the value array
            if (isalpha(line[i])) {
                value[valueIndex++] = line[i];
            } else {
                // If the value array has any alphabetic characters, null-terminate and print it
                if (valueIndex > 0) {
                    value[valueIndex] = '\0'; // Null-terminate the string
                    printf("Alphabetic sequence: %s\n", value);
                    if (check_for_keyword(value)) {
                        extern Node* root;  // BST root declared in bst.c
                        LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
                        list->head = NULL;
                        ListNode *node1 = create_node('a', 'A'); // Example values
                        insert(node1, list, false);
                        root = insertNode(root, "hello", "<html><body><h1>Hello, World!</h1></body></html>");
                    }
                    valueIndex = 0; // Reset the index for the next sequence
                }
            }
        }

        // If the line ends with an alphabetic sequence, print it
        if (valueIndex > 0) {
            value[valueIndex] = '\0'; // Null-terminate the string
            printf("Alphabetic sequence: %s\n", value);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}