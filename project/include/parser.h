#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include "utils.h"

typedef enum {
    L_STR,
    L_FROM,
    L_TO,
    L_DATE,
    L_BOUND,
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
    S_PARTS,
    S_PEND,
    S_COUNT,
    S_END,
    S_ERR
} state_t;

typedef struct {
    char *from;
    char *to;
    char *date;
    char *bound;
    size_t parts_count;
} data_t;

typedef int (*action_t)(const char *s, data_t *eml_data);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static rule_t syntax[S_COUNT][L_COUNT] = {
//             L_STR           L_FROM          L_TO            L_DATE          L_BOUND         L_DASH          L_EOF
/*S_BEGIN*/  {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}},
/*S_HEADER*/ {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}},
/*S_TEXT*/   {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}},
/*S_BVALUE*/ {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}},
/*S_PARTS*/  {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}},
/*S_PEND*/   {{S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL},  {S_ERR, NULL}}
};

int eml_parse(const char *filename);

#endif  // PROJECT_INCLUDE_PARSER_H_