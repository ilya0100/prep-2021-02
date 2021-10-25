#ifndef PROJECT_INCLUDE_LOGIC_TEST_H_
#define PROJECT_INCLUDE_LOGIC_TEST_H_

#include "utils.h"

void write_data_to_file(const char *filename);
void transaction_write(const char *filename);
void write_transfer_to_file(const char *client_filename,
    const char *transaction_filename,
    const char *blackrecord_filename);

#endif  // PROJECT_INCLUDE_LOGIC_TEST_H_
