#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define FILENAME "transaction.dat"

typedef struct Data {
	int Number;
	char Name[20];
	char Surname[20];
	char addres[30];
	char TelNumber[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
} Data;

#endif  // PROJECT_INCLUDE_UTILS_H_
