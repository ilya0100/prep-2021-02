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
#define PRINT_INPUT_FIELD() printf("%s\n%s\n", "1 Number account: ", "2 Client cash payments: ")

void write_input_to_file(const char *filename) {
	ClientData client = {0};
	FILE *fd_of_filename = fopen(filename, "r+");
	if(fd_of_filename == NULL) {
		puts("Not access");
	} else {
		PRINT_OUTPUT_MESSAGE();
		while(read_client_data_from_file(stdin, &client) != -1) {
			write_client_data_to_file(fd_of_filename, &client);
			PRINT_OUTPUT_MESSAGE();
		}
		fclose(fd_of_filename);
	}
}

void transaction_write(const char *filename) {
	ClientData transfer = {0};
	FILE *fd_of_filename = fopen(filename, "r+");
	if(fd_of_filename == NULL) {
		puts("Not access");
	} else {
		PRINT_INPUT_FIELD();
		while (scanf("%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
			fprintf(fd_of_filename, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
			PRINT_INPUT_FIELD();
		}
		fclose(fd_of_filename);
	}
}

void write_transfer_to_file(const char *client_filename,
	const char *transaction_filename,
	const char *blackrecord_filename) {
	ClientData client = {0}, transfer = {0};
	FILE *fd_of_client_file = fopen(client_filename, "r");
	FILE *fd_of_transaction_file = fopen(transaction_filename, "r");
	FILE *fd_of_blackrecord = fopen(blackrecord_filename, "w");
	if (fd_of_client_file == NULL) {
		puts("exit");
		fclose(fd_of_transaction_file);
		fclose(fd_of_blackrecord);
		return;
	}
	if (fd_of_transaction_file == NULL) {
		puts("exit");
		fclose(fd_of_client_file);
		fclose(fd_of_blackrecord);
		return;
	}
	if (fd_of_blackrecord == NULL) {
		puts("exit");
		fclose(fd_of_client_file);
		fclose(fd_of_transaction_file);
		return;
	}
	while (read_client_data_from_file(fd_of_client_file, &client) != -1) {
		while (fscanf(fd_of_transaction_file, "%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
			if (client.number == transfer.number && transfer.cash_payments != 0) {
				client.credit_limit += transfer.cash_payments;
			}
		}
		write_client_data_to_file(fd_of_blackrecord, &client);
		rewind(fd_of_transaction_file);
	}
	fclose(fd_of_client_file);
	fclose(fd_of_transaction_file);
	fclose(fd_of_blackrecord);
}
