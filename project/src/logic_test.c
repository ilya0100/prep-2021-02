#include "input_output_test.c"
#include "logic_test.h"

#define PRINT_OUTPUT_MESSAGE() printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", \
	"1 Number account: ", \
	"2 Client name: ", \
	"3 Surname: ", \
	"4 Addres client: ", \
	"5 Client Telnum: ", \
	"6 Client indebtedness: ", \
	"7 Client credit limit: ", \
	"8 Client cash payments: ")

void write_data_to_file(const char *filename) {
	Data client = {0};
	FILE *Ptr = fopen(filename, "r+");
	if(Ptr == NULL) {
		puts("Not acess");
	} else {
		PRINT_OUTPUT_MESSAGE();
		while(read_from_file(stdin, &client) != -1) {
			write_to_file(Ptr, &client);
			PRINT_OUTPUT_MESSAGE();
		}
		fclose(Ptr);
	}
}

void transaction_write(const char *filename) {
	Data transfer = {0};
	FILE *Ptr = fopen(filename, "r+");
	if(Ptr == NULL) {
		puts("Not acess");
	} else {
		printf("%s\n%s\n",
			"1 Number account: ",
			"2 Client cash payments: ");
		while (scanf("%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
			fprintf(Ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
			printf("%s\n%s\n",
				"1 Number account:",
				"2 Client cash payments: ");
		}
		fclose(Ptr);
	}
}

void write_transfer_to_file(const char *client_filename,
	const char *transaction_filename,
	const char *blackrecord_filename) {
	Data client = {0}, transfer = {0};
	FILE *Ptr, *Ptr_2, *blackrecord;
	Ptr = fopen(client_filename, "r");
	Ptr_2 = fopen(transaction_filename, "r");
	blackrecord = fopen(blackrecord_filename, "w");
	if (Ptr == NULL) {
		puts("exit");
		fclose(Ptr_2);
		fclose(blackrecord);
	} else if (Ptr_2 == NULL) {
		puts("exit");
		fclose(Ptr);
		fclose(blackrecord);
	} else if (blackrecord == NULL) {
		puts("exit");
		fclose(Ptr);
		fclose(Ptr_2);
	} else {
		while (read_from_file(Ptr, &client) != -1) {
			while (fscanf(Ptr_2, "%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
				if (client.number == transfer.number && transfer.cash_payments != 0) {
					client.credit_limit += transfer.cash_payments;
				}
			}
			write_to_file(blackrecord, &client);
			rewind(Ptr_2);
		}
		fclose(Ptr);
		fclose(Ptr_2);
		fclose(blackrecord);
	}
}
