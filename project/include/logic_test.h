#ifndef PROJECT_INCLUDE_LOGIC_TEST_H_
#define PROJECT_INCLUDE_LOGIC_TEST_H_

#include "utils.h"

void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPTR, Data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

#endif  // PROJECT_INCLUDE_LOGIC_TEST_H_
