#include "main_module.h"

void test_write_to_file() {
	const char *filename = "test_file.dat";
	FILE *Ptr;
	Ptr = fopen(filename , "w");
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
		struct some got_data = {0};
		read_from_file(Ptr, &got_data);
		if (expected_data.Number == got_data.Number &&
			expected_data.Name == got_data.Name &&
			expected_data.Surname == got_data.Surname &&
			expected_data.addres == got_data.addres &&
			expected_data.TelNumber == got_data.TelNumber &&
			expected_data.indebtedness == got_data.indebtedness &&
			expected_data.credit_limit == got_data.credit_limit &&
			expected_data.cash_payments == got_data.cash_payments) {
				printf("%s\n", "TEST SUCCEED");
		} else {
			printf("%s\n", "TEST FAILED");
		}
	}
}

void write_to_file(FILE *ofPtr, struct some *data) {
    fprintf(ofPtr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
		data->Number,
		data->Name,
		data->Surname,
		data->addres,
		data->TelNumber,
		data->indebtedness,
		data->credit_limit,
		data->cash_payments);
	fclose(ofPtr);
}

void read_from_file(FILE *ofPtr, struct some *data) {
    fscanf(ofPtr, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
		&data->Number,
		data->Name,
		data->Surname,
		data->addres,
		data->TelNumber,
		&data->indebtedness,
		&data->credit_limit,
		&data->cash_payments);
	fclose(ofPtr);
}
