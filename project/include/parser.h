#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define STRING_LENGTH 500

typedef struct {
    char from[STRING_LENGTH];
    char to[STRING_LENGTH];
    char date[STRING_LENGTH];
    char bound[STRING_LENGTH];
    size_t bound_size;
    size_t parts_count;
} data_t;

int get_eml(const char *path_to_eml, data_t *eml_data);

#endif  // PROJECT_INCLUDE_PARSER_H_
