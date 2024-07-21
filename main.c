#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h> 
#include "bst.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    _KEYWORD_,
    _SEPARATOR_,
    _VALUE_,
    _UNKNOWN_,  // Added for unrecognized tokens
    _VARIABLE_,
} TYPE;

typedef enum {
    _FOR_,
    _IN_,
    _NONE_  // No keyword matched
} KEYWORD;

typedef enum {
    _EQUALS_,
    _SEPARATOR_NONE_  // No separator matched
} SEPARATOR;

typedef enum {
    _INT_,
    _FLOAT_,
    _STRING_,
    _VALUE_NONE_  // No value matched
} VALUE;

typedef struct {
    TYPE token_type;
    union {
        KEYWORD keyword;
        SEPARATOR separator;
        VALUE value;
    } token_value;
    char str[256];  // To store the actual token string
} TOKEN;

// Function prototypes
TYPE determine_type(const char *token, TOKEN *t);

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
        char *token = strtok(line, " \t\n");  // Tokenize by spaces, tabs, and newlines
        while (token != NULL) {
            TOKEN t;
            if (determine_type(token, &t) != _UNKNOWN_) {
                printf("Token: %s, Type: %d\n", t.str, t.token_type);
            }
            token = strtok(NULL, " \t\n");
        }
    }

    // Close the file
    fclose(file);

    return 0;
}

TYPE determine_type(const char *token, TOKEN *t) {
    // Check if keyword
    if (strcmp(token, "for") == 0) {
        t->token_type = _KEYWORD_;
        t->token_value.keyword = _FOR_;
    } else if (strcmp(token, "in") == 0) {
        t->token_type = _KEYWORD_;
        t->token_value.keyword = _IN_;
    } else if (strcmp(token, "=") == 0) {
        t->token_type = _SEPARATOR_;
        t->token_value.separator = _EQUALS_;
    } else if (isdigit(token[0])) {  // Simple check for integer
        t->token_type = _VALUE_;
        t->token_value.value = _INT_;
    } else {
        t->token_type = _VARIABLE_;  // No recognized type
        t->token_value.value = _STRING_;
    }

    strcpy(t->str, token);
    return t->token_type;
}
