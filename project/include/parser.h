#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 250
#define BOUNDARY "boundary="
#define FROM "From:"
#define TO "To:"
#define DATE "Date:"

typedef enum {
    L_FROM,
    L_TO,
    L_DATE,
    L_CONTENT,
    L_STR,
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
    char *from;
    char *to;
    char *date;
    char *bound;
    size_t bound_size;
    int bound_status;
    size_t parts_count;
} eml_data_t;

typedef struct {
    char *data;
    size_t size;
    size_t length;
} string_t;

typedef int (*action_t)(string_t *str, eml_data_t *eml_data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

eml_data_t *create_data();
void free_data(eml_data_t *eml_data);

int get_eml(const char *path_to_eml, eml_data_t *eml_data);

#endif  // PROJECT_INCLUDE_PARSER_H_
