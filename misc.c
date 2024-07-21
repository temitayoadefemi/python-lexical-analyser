int check_for_keyword(char *value) {
    if (strcmp(value, "for") != 0 && strcmp(value, "in") != 0 && strcmp(value, "print") != 0) {
        add_value(value);
        printf("Added Value: %s\n", value);
        return 1;
    } else {
        return 0;
    }
}
