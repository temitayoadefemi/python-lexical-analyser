#include <bst.h>
#include <stdio.h>
#include <stdlib.h>


int check_for_keyword(char *value) {
    if (strcmp(value, "for") != 0 && strcmp(value, "in") != 0 && strcmp(value, "print") != 0) {
        add_value(value);
        printf("Added Value: %s\n", value);
        return 1;
    } else {
        return 0;
    }
}

void process_value(char *value, int *valueIndex, int *capturing_value, int *captured) {
    if (*valueIndex > 0) {
        value[*valueIndex] = '\0';  // Null-terminate the string
        if (*capturing_value) {
            printf("Value after '=': %s\n", value);
            char* key = get_last_value();
            Node* node = NULL;  // Initialize the node
            node = insertNode(node, key, value);
            printf("Key %s, Value %s\n", key, value);
            *capturing_value = 0;  // Stop capturing after a complete value
            *captured = 1;
        } else {
            printf("Alphabetic sequence: %s\n", value);
            int result = check_for_keyword(value);
        }
        *valueIndex = 0;  // Reset the index for next usage
    }
}

// A