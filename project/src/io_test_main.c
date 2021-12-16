#include "input_output_test.h"

int main() {
	const char *filename = "test_file.dat";
	ClientData expected_data = {
    	.number = 1,
    	.name = "ivan",
    	.surname = "ivanov",
    	.addres = "addres_1",
    	.tel_number = "8800",
    	.indebtedness = 555,
    	.credit_limit = 35,
    	.cash_payments = 35
    };
	FILE *datafile = fopen(filename , "w");
	write_client_data_to_file(datafile, &expected_data);
	fclose(datafile);
	ClientData got_data = {0};
	datafile = fopen(filename , "r");
	read_client_data_from_file(datafile, &got_data);
	fclose(datafile);
	if (expected_data.number == got_data.number &&
		!strcmp(expected_data.name, got_data.name) &&
		!strcmp(expected_data.surname, got_data.surname) &&
		!strcmp(expected_data.addres, got_data.addres) &&
		!strcmp(expected_data.tel_number, got_data.tel_number) &&
		expected_data.indebtedness == got_data.indebtedness &&
		expected_data.credit_limit == got_data.credit_limit &&
		expected_data.cash_payments == got_data.cash_payments) {
		printf("%s\n", "TEST SUCCEED");
	} else {
		printf("%s\n", "TEST FAILED");
	}
	return 0;
}
