#ifndef PROJECT_INCLUDE_LOGIC_TEST_H_
#define PROJECT_INCLUDE_LOGIC_TEST_H_

#include "utils.h"

void write_data_to_file(FILE *ofPTR, Data Client);
void transaction_write(FILE *ofPTR, Data transfer);
void write_transfer_to_file(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

#endif  // PROJECT_INCLUDE_LOGIC_TEST_H_
