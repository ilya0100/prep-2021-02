#include "input_output_test.h"

int main() {
	const char *filename = "test_file.dat";
	Data expected_data = {
    	.number = 1,
    	.name = "ivan",
    	.surname = "ivanov",
    	.addres = "addres_1",
    	.tel_number = "8800",
    	.indebtedness = 555,
    	.credit_limit = 35,
    	.cash_payments = 35
    };
	write_to_file(filename, &expected_data);
	Data got_data = {0};
	read_from_file(filename, &got_data);
	if (expected_data.number == got_data.number &&
		strcmp(expected_data.name, got_data.name) == 0 &&
		strcmp(expected_data.surname, got_data.surname) == 0 &&
		strcmp(expected_data.addres, got_data.addres) == 0 &&
		strcmp(expected_data.tel_number, got_data.tel_number) == 0 &&
		expected_data.indebtedness == got_data.indebtedness &&
		expected_data.credit_limit == got_data.credit_limit &&
		expected_data.cash_payments == got_data.cash_payments) {
		printf("%s\n", "TEST SUCCEED");
	} else {
		printf("%s\n", "TEST FAILED");
	}
	return 0;
}
