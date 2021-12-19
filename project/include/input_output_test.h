#ifndef PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_
#define PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_

#include "utils.h"

void write_client_data_to_file(FILE *datafile, ClientData *data);
int read_client_data_from_file(FILE *datafile, ClientData *data);

#endif  // PROJECT_INCLUDE_INPUT_OUTPUT_TEST_H_
