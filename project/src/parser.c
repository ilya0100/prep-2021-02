#include "parser.h"

#define STRING_LENGTH 500

int get_from(const char *s, data_t *eml_data) {
    if (s == NULL) {
        return -1;
    }
    strcpy(eml_data->from, s + sizeof("From:"));
    return 0;
}

int get_to(const char *s, data_t *eml_data) {
    if (s == NULL) {
        return -1;
    }
    strcpy(eml_data->to, s + sizeof("To:"));
    return 0;
}

int get_date(const char *s, data_t *eml_data) {
    if (s == NULL) {
        return -1;
    }
    strcpy(eml_data->date, s + sizeof("Date:"));
    return 0;
}

int get_bound(const char *s, data_t *eml_data) {
    if (s == NULL) {
        return -1;
    }
    char *buffer = strstr(s, "boundary=") + sizeof("boundary=");
    if (*buffer == '"') {
        buffer++;
    }
    size_t bound_size = 0;
    while (!isspace(*(buffer + bound_size))) {
        if (*(buffer + bound_size) == '"') {
            break;
        }
        bound_size++;
    }
    strncpy(eml_data->bound, buffer, bound_size);
    return 0;
}

lexem_t get_lexem(const char *s) {
    if (s == NULL) {
        return -1;
    }
    if (strstr(s, "From:") != NULL) {
        return L_FROM;
    } 
    if (strstr(s, "To:") != NULL) {
        return L_TO;
    }
    if (strstr(s, "Date:") != NULL) {
        return L_DATE;
    }
    if (strstr(s, "boundary=") != NULL) {
        return L_BOUND;
    }
    if (s[0] == '-') {
        return L_DASH;
    }
    return L_STR;
}

int get_eml(FILE* eml_file, data_t *eml_data) {
    state_t state = S_BEGIN;
    char s[STRING_LENGTH] = "";
    char *buffer = "";
    // size_t buffer_size = 0;
    do { 
        if (s[0] == ' ') {
            buffer = strcat(buffer, s);
            // buffer_size += strlen(s);
        } else {
            // char *end;
            lexem_t lexem = get_lexem(buffer);
            if (lexem == L_ERR) {
                return -1;
            }
            rule_t rule = syntax[state][lexem];
            if (rule.state == S_ERR) {
                return -1;
            }
            if (rule.action != NULL) {
                if (rule.action(buffer, eml_data) == -1) {
                    return -1;
                }
            }
            if (rule.state == S_END) {
                return 0;
            }
            state = rule.state;
            buffer = "";
            // buffer_size = 0;
        }
    } while (fgets(s, STRING_LENGTH, eml_file) != NULL);
    return -1;
}


int eml_parse(const char *filename) {
    FILE* eml_file = fopen(filename, "r");
    if (eml_file == NULL) {
        return -1;
    }
    data_t eml_data = {0};
    get_eml(eml_file, &eml_data);
    free(eml_file);
    return 0;
}