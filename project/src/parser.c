#include "parser.h"

#define READ_MULTILINE_HEADER \
    char buffer[STRING_LENGTH] = ""; \
    while (fgets(buffer, STRING_LENGTH, eml_file) != NULL) { \
        size_t buf_len = strlen(buffer); \
        if (*buffer == ' ' || *buffer == '\t') { \
            strncat(*end, buffer, buf_len); \
        } else { \
            if (fseek(eml_file, - buf_len, SEEK_CUR)) { \
                perror("error"); \
            } \
            break; \
        } \
    }

typedef enum {
    L_STR,
    L_FROM,
    L_TO,
    L_DATE,
    L_BOUNDARY,
    L_DASH,
    L_EOF,
    L_COUNT,
    L_ERR
} lexem_t;

typedef enum {
    S_BEGIN,
    S_HEADER,
    S_TEXT,
    S_BVALUE,
    S_BOUND,
    S_PARTS,
    S_COUNT,
    S_END,
    S_ERR
} state_t;

typedef int (*action_t)(FILE *eml_file, char **end, data_t *eml_data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static int get_from(FILE *eml_file, char **end, data_t *eml_data) {
    if (*end == NULL || eml_file == NULL) {
        return -1;
    }
    READ_MULTILINE_HEADER
    size_t length = strlen(*end);
    memcpy(eml_data->from, *end, length - 1);
    return 0;
}

static int get_to(FILE *eml_file, char **end, data_t *eml_data) {
    if (*end == NULL || eml_file == NULL) {
        return -1;
    }
    READ_MULTILINE_HEADER
    size_t length = strlen(*end);
    memcpy(eml_data->to, *end, length - 1);
    return 0;
}

static int get_date(FILE *eml_file, char **end, data_t *eml_data) {
    if (*end == NULL || eml_file == NULL) {
        return -1;
    }
    READ_MULTILINE_HEADER
    size_t length = strlen(*end);
    memcpy(eml_data->date, *end, length - 1);
    return 0;
}

static int get_bound(FILE *eml_file, char **end, data_t *eml_data) {
    if (*end == NULL || eml_file == NULL) {
        return -1;
    }
    if (**end == '"') {
        (*end)++;
    }
    size_t bound_size = 0;
    while (!isspace(*(*end + bound_size))) {
        if (*(*end + bound_size) == '"') {
            break;
        }
        bound_size++;
    }
    memcpy(eml_data->bound, *end, bound_size);
    eml_data->bound_size = bound_size;
    return 0;
}

static int comp_bound(FILE *eml_file, char **end, data_t *eml_data) {
    if (*end == NULL || eml_file == NULL) {
        return -1;
    }
    if (!strncmp(*end, eml_data->bound, eml_data->bound_size)) {
        eml_data->parts_count++;
    }
    return 0;
}

static rule_t syntax[S_COUNT][L_COUNT] = {
//             L_STR            L_FROM                 L_TO                 L_DATE                 L_BOUNDARY             L_DASH          L_EOF
/*S_BEGIN*/  {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},  {S_ERR, NULL},         {S_ERR, NULL},  {S_END, NULL}},
/*S_HEADER*/ {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},  {S_BVALUE, get_bound}, {S_ERR, NULL},  {S_ERR, NULL}},
/*S_TEXT*/   {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},  {S_BVALUE, get_bound}, {S_BOUND, comp_bound},{S_END, NULL}},
/*S_BVALUE*/ {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},  {S_TEXT, NULL},        {S_ERR, NULL},  {S_ERR, NULL}},
/*S_BOUND*/  {{S_PARTS, NULL}, {S_ERR, NULL},         {S_ERR, NULL},       {S_ERR, NULL},         {S_ERR, NULL},         {S_END, NULL},  {S_ERR, NULL}},
/*S_PARTS*/  {{S_PARTS, NULL}, {S_ERR, NULL},         {S_ERR, NULL},       {S_ERR, NULL},         {S_ERR, NULL},         {S_BOUND, comp_bound},{S_ERR, NULL}},
};

static lexem_t get_lexem(char *s, char **end) {
    if (s == NULL) {
        return L_ERR;
    }
    if (*s == EOF) {
        return L_EOF;
    }
    char *buffer = strstr(s, "From:");
    if (buffer != NULL && *buffer == *s) {
        *end = buffer;
        *end += sizeof("From:");
        return L_FROM;
    }
    buffer = strstr(s, "To:");
    if (buffer != NULL && *buffer == *s) {
        *end = buffer;
        *end += sizeof("To:");
        return L_TO;
    }
    buffer = strstr(s, "Date:");
    if (buffer != NULL && *buffer == *s) {
        *end = buffer;
        *end += sizeof("Date:");
        return L_DATE;
    }
    buffer = strstr(s, "boundary=");
    if (buffer != NULL) {
        *end = buffer;
        *end += sizeof("boundary=") - 1;
        return L_BOUNDARY;
    }
    if (*s == '-' && *(s + 1) == '-') {
        *end += sizeof("--") - 1;
        return L_DASH;
    }
    *end = s;
    return L_STR;
}

int get_eml(const char *path_to_eml, data_t *eml_data) {
    FILE *eml_file = fopen(path_to_eml, "r");
    if (eml_file == NULL) {
        return -1;
    }
    state_t state = S_BEGIN;
    char *end;
    char s[STRING_LENGTH] = "";
    while (fgets(s, STRING_LENGTH, eml_file) != NULL) {
        lexem_t lexem = get_lexem(s, &end);
        if (lexem == L_ERR) {
            return -1;
        }
        rule_t rule = syntax[state][lexem];
        if (rule.state == S_ERR) {
            return 0;
        }
        if (rule.action != NULL) {
            if (rule.action(eml_file, &end, eml_data) == -1) {
                return -1;
            }
        }
        if (rule.state == S_BOUND && strstr(end, "--") != NULL) {
            lexem = L_DASH;
            rule = syntax[state][lexem];
        }
        if (rule.state == S_END) {
            return 0;
        }
        state = rule.state;
    }
    free(eml_file);
    return -1;
}
