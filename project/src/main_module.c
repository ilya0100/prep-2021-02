#include "main_module.h"

int main() {
	const char *filename = "test_file.dat";
	FILE *Ptr;
	Ptr = fopen(filename , "r+");
	if (Ptr == NULL) {
		puts("ERROR!");
	} else {
		struct some expected_data = {
        	.Number = 1,
        	.Name = "ivan",
        	.Surname = "ivanov",
        	.addres = "addres_1",
        	.TelNumber = "8800",
        	.indebtedness = 555,
        	.credit_limit = 35,
        	.cash_payments = 35
    	};
		write_to_file(Ptr, &expected_data);
		rewind(Ptr);
		struct some got_data = {0};
		read_from_file(Ptr, &got_data);
		if (expected_data.Number == got_data.Number &&
			strcmp(expected_data.Name, got_data.Name) == 0 &&
			strcmp(expected_data.Surname, got_data.Surname) == 0 &&
			strcmp(expected_data.addres, got_data.addres) == 0 &&
			strcmp(expected_data.TelNumber, got_data.TelNumber) == 0 &&
			expected_data.indebtedness == got_data.indebtedness &&
			expected_data.credit_limit == got_data.credit_limit &&
			expected_data.cash_payments == got_data.cash_payments) {
				printf("%s\n", "TEST SUCCEED");
		} else {
			printf("%s\n", "TEST FAILED");
		}
	}
}
