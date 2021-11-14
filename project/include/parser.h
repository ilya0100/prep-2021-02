#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#define _GNU_SOURCE

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
    char *from;
    char *to;
    char *date;
    char *bound;
    size_t bound_size;
    int bound_status;
    size_t parts_count;
} data_t;

data_t *create_data();
void free_data(data_t *eml_data);

int get_eml(const char *path_to_eml, data_t *eml_data);

#endif  // PROJECT_INCLUDE_PARSER_H_
