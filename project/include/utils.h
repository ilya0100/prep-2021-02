#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
	int number;
	char name[20];
	char surname[20];
	char addres[30];
	char tel_number[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
} ClientData;

#endif  // PROJECT_INCLUDE_UTILS_H_
