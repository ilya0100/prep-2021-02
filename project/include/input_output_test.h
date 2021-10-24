#ifndef PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_
#define PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_

#include <string.h>
#include "utils.h"

void write_to_file(FILE *ofPtr, Data *data);
void read_from_file(FILE *ofPtr, Data *data);

#endif  // PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_
