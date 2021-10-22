#ifndef PROJECT_INCLUDE_MAIN_MODULE_H_
#define PROJECT_INCLUDE_MAIN_MODULE_H_

#include <stdio.h>
#include <stdlib.h>

struct some {
	int Number;
	char Name[20];
	char Surname[20];
	char addres[30];
	char TelNumber[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
};

void write_to_file(FILE *ofPtr, struct some *data);
void read_from_file(FILE *ofPtr, struct some *data);

#endif  // PROJECT_INCLUDE_MAIN_MODULE_H_
