#include "parser.h"

typedef enum {
    L_STR,
    L_FROM,
    L_TO,
    L_DATE,
    L_CONTENT,
    L_DASH,
    L_NULL,
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
    S_END,
    S_COUNT,
} state_t;

typedef struct {
    char *data;
    size_t size;
    ssize_t length;
} string_t;

string_t *create_string_t() {
    string_t *new_string = malloc(sizeof(string_t));
    if (new_string == NULL) {
        return NULL;
    }
    new_string->data = malloc(sizeof(char));
    new_string->length = 0;
    new_string->size = 0;
    return new_string;
}

void free_string_t(string_t *str) {
    if (str != NULL && str->data != NULL) {
        free(str->data);
    }
    if (str !=NULL) {
        free(str);
    }
}

data_t *create_data() {
    data_t *eml_data = malloc(sizeof(data_t));
    if (eml_data == NULL) {
        return NULL;
    }
    eml_data->from = calloc(1, sizeof(char));
    eml_data->to = calloc(1, sizeof(char));
    eml_data->date = calloc(1, sizeof(char));
    eml_data->bound = calloc(1, sizeof(char));
    eml_data->bound_size = 0;
    eml_data->bound_status = 0;
    eml_data->parts_count = 0;
    if (eml_data->from == NULL || eml_data->to == NULL ||
        eml_data->date == NULL || eml_data->bound == NULL) {
        free_data(eml_data);
        return NULL;
    }
    return eml_data;
}

void free_data(data_t *eml_data) {
    if (eml_data->from != NULL) {
        free(eml_data->from);
    }
    if (eml_data->to != NULL) {
        free(eml_data->to);
    }
    if (eml_data->date != NULL) {
        free(eml_data->date);
    }
    if (eml_data->bound != NULL) {
        free(eml_data->bound);
    }
    if (eml_data != NULL) {
        free(eml_data);
    }
}

typedef int (*action_t)(FILE *eml_file, string_t *str, data_t *eml_data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static int copy_string_without_ws(char **data, string_t *str, size_t number_of_skips) {
    if (*data == NULL || str == NULL) {
        return -1;
    }
    char *buffer = str->data;
    if (isspace(*(buffer + number_of_skips))) {
        number_of_skips++;
    }
    size_t length = 0;
    for (ssize_t i = number_of_skips; i <= str->length; ++i) {
        if (buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != '\t') {
            *(*data + length) = buffer[i];
            length++;
        }
    }
    return 0;
}

static string_t *get_string(FILE *eml_file) {
    if (eml_file == NULL) {
        return NULL;
    }
    string_t *new_str = create_string_t();
    if ((new_str->length = getline(&new_str->data, &new_str->size, eml_file)) == -1) {
        free_string_t(new_str);
        return NULL;
    }
    *(new_str->data + new_str->length) = '\0';
    new_str->data = realloc(new_str->data, new_str->size);
    return new_str;
}

static int read_multiline_header(FILE *eml_file, string_t *str) {
    if (str == NULL) {
        return -1;
    }
    while (1) {
        string_t *buffer = get_string(eml_file);
        if (buffer == NULL) {
            break;
        }
        if (*buffer->data == ' ' || *buffer->data == '\t') {
            str->size = str->size + buffer->size;
            str->length = str->length + buffer->length;
            str->data = realloc(str->data, str->size);
            strncat(str->data, buffer->data, buffer->length);
        } else {
            if (fseek(eml_file, - buffer->length, SEEK_CUR)) {
                perror("error");
            }
            break;
        }
        free_string_t(buffer);
    }
    return 0;
}

static int get_from(FILE *eml_file, string_t *str, data_t *eml_data) {
    if (str == NULL || eml_file == NULL) {
        return -1;
    }
    if (*eml_data->from) {
        return 0;
    }
    if (read_multiline_header(eml_file, str) == -1) {
        return -1;
    }
    size_t eml_size = str->size;
    eml_data->from = realloc(eml_data->from, eml_size);
    if (eml_data->from == NULL) {
        return -1;
    }
    if (copy_string_without_ws(&eml_data->from, str, sizeof("From:") - 1) == -1) {
        free(eml_data->from);
        return -1;
    }
    return 0;
}

static int get_to(FILE *eml_file, string_t *str, data_t *eml_data) {
    if (str == NULL || eml_file == NULL) {
        return -1;
    }
    if (*eml_data->to) {
        return 0;
    }
    if (read_multiline_header(eml_file, str) == -1) {
        return -1;
    }
    size_t eml_size = str->size;
    eml_data->to = realloc(eml_data->to, eml_size);
    if (eml_data->to == NULL) {
        return -1;
    }
    if (copy_string_without_ws(&eml_data->to, str, sizeof("To:") - 1) == -1) {
        free(eml_data->to);
        return -1;
    }
    return 0;
}

static int get_date(FILE *eml_file, string_t *str, data_t *eml_data) {
    if (str == NULL || eml_file == NULL) {
        return -1;
    }
    if (*eml_data->date) {
        return 0;
    }
    if (read_multiline_header(eml_file, str) == -1) {
        return -1;
    }
    size_t eml_size = str->size;
    eml_data->date = realloc(eml_data->date, eml_size);
    if (eml_data->date == NULL) {
        return -1;
    }
    if (copy_string_without_ws(&eml_data->date, str, sizeof("Date:") - 1) == -1) {
        free(eml_data->date);
        return -1;
    }
    return 0;
}

static int get_bound(FILE *eml_file, string_t *str, data_t *eml_data) {
    if (str == NULL || eml_file == NULL) {
        return -1;
    }
    if (read_multiline_header(eml_file, str) == -1) {
        return -1;
    }
    if (eml_data->parts_count == 1 && eml_data->bound_size == 0) {
        return 0;
    }
    char *buffer = strstr(str->data, "boundary=");
    if (buffer == NULL) {
        buffer = strstr(str->data, "BOUNDARY=");
    }
    if (buffer == NULL || (*(buffer - 1) >= 'a' && *(buffer - 1) <= 'z')) {
        eml_data->parts_count = 1;
        eml_data->bound_size = 0;
        return 0;
    }
    buffer += sizeof("boundary=") - 1;
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
    if (bound_size == 0) {
        return -1;
    }
    eml_data->bound = realloc(eml_data->bound, bound_size * sizeof(char));
    memcpy(eml_data->bound, buffer, bound_size);
    eml_data->bound_size = bound_size;
    return 0;
}

static int comp_bound(FILE *eml_file, string_t *str, data_t *eml_data) {
    if (str == NULL || eml_file == NULL) {
        return -1;
    }
    if (eml_data->bound_size == 0) {
        return 0;
    }
    if (!strncmp(str->data + sizeof("--") - 1, eml_data->bound, eml_data->bound_size)) {
        eml_data->parts_count++;
        eml_data->bound_status = 1;
    } else {
        eml_data->bound_status = 0;
    }
    return 0;
}

static rule_t syntax[S_COUNT][L_COUNT] = {
//             L_STR            L_FROM                 L_TO                 L_DATE L_CONTENT L_DASH L_NULL
/*S_BEGIN*/  {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},
{S_BVALUE, get_bound}, {S_TEXT, NULL},  {S_END, NULL}},
/*S_HEADER*/ {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},
{S_BVALUE, get_bound}, {S_TEXT, NULL},  {S_END, NULL}},
/*S_TEXT*/   {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},
{S_BVALUE, get_bound}, {S_BOUND, comp_bound}, {S_END, NULL}},
/*S_BVALUE*/ {{S_TEXT, NULL},  {S_HEADER, get_from},  {S_HEADER, get_to},  {S_HEADER, get_date},
{S_TEXT, NULL},        {S_TEXT, NULL},  {S_END, NULL}},
/*S_BOUND*/  {{S_PARTS, NULL}, {S_PARTS, NULL},       {S_PARTS, NULL},     {S_PARTS, NULL},
{S_PARTS, NULL},       {S_BOUND, comp_bound}, {S_END, NULL}},
/*S_PARTS*/  {{S_PARTS, NULL}, {S_PARTS, NULL},       {S_PARTS, NULL},     {S_PARTS, NULL},
{S_PARTS, NULL},       {S_BOUND, comp_bound}, {S_END, NULL}},
};

static lexem_t get_lexem(const string_t *str) {
    if (str == NULL) {
        return L_ERR;
    }
    if (strstr(str->data, "From:") == str->data) {
        return L_FROM;
    }
    if (strstr(str->data, "To:") == str->data) {
        return L_TO;
    }
    if (strstr(str->data, "Date:") == str->data) {
        return L_DATE;
    }
    if (strstr(str->data, "Content-Type:") == str->data) {
        return L_CONTENT;
    }
    if (*str->data == '-' && *(str->data + 1) == '-') {
        return L_DASH;
    }
    return L_STR;
}

int get_eml(const char *path_to_eml, data_t *eml_data) {
    FILE *eml_file = fopen(path_to_eml, "r");
    if (eml_file == NULL) {
        return -1;
    }
    state_t state = S_BEGIN;
    lexem_t lexem;
    while (1) {
        string_t *str = get_string(eml_file);
        if (str == NULL) {
            lexem = L_NULL;
        } else {
            lexem = get_lexem(str);
        }
        if (lexem == L_ERR) {
            free_string_t(str);
            free(eml_file);
            return -1;
        }
        rule_t rule = syntax[state][lexem];
        if (rule.action != NULL) {
            if (rule.action(eml_file, str, eml_data) == -1) {
                free_string_t(str);
                free(eml_file);
                return -1;
            }
        }
        if (eml_data->bound_status &&
            strstr(str->data + eml_data->bound_size + sizeof ("--") - 1, "--")) {
            eml_data->parts_count--;
            rule.state = S_END;
        } else {
            eml_data->bound_status = 0;
        }
        if (rule.state == S_END) {
            free(eml_file);
            return 0;
        }
        state = rule.state;
        free_string_t(str);
    }
    free(eml_file);
    return -1;
}
