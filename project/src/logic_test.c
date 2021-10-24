#include "input_output_test.c"
#include "logic_test.h"

void write_data_to_file() {
	Data client = {0};
	FILE *Ptr = fopen("record.dat", "r+");
	if(Ptr == NULL) {
		puts("Not acess");
	} else {
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: ");
		while(scanf("%12d%11s%11s%16s%20s%12lf%12lf%12lf",
				&client.number,
				client.name,
				client.surname,
				client.addres,
				client.tel_number,
				&client.indebtedness,
				&client.credit_limit,
				&client.cash_payments) != -1) {
			write_to_file(Ptr, &client);
			printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
				"1 Number account: ",
				"2 Client name: ",
				"3 Surname: ",
				"4 Addres client: ",
				"5 Client Telnum: ",
				"6 Client indebtedness: ",
				"7 Client credit limit: ",
				"9 Client cash payments:");
		}
		fclose(Ptr);
	}
}

void transaction_write() {
	Data transfer = {0};
	FILE *Ptr = fopen("transaction.dat", "r+");
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

void write_transfer_to_file() {
	Data client_data = {0}, transfer = {0};
	FILE *Ptr, *Ptr_2, *blackrecord;
	Ptr = fopen("record.dat", "r");
	Ptr_2 = fopen("transaction.dat", "r");
	blackrecord = fopen("blackrecord.dat", "w");
	if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
		puts("exit");
	} else {
		while (fscanf(Ptr, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
			&client_data.number,
			client_data.name,
			client_data.surname,
			client_data.addres,
			client_data.tel_number,
			&client_data.indebtedness,
			&client_data.credit_limit,
			&client_data.cash_payments) != -1) {
			while (fscanf(Ptr_2, "%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
				if (client_data.number == transfer.number && transfer.cash_payments != 0) {
					client_data.credit_limit += transfer.cash_payments;
				}
			}
			write_to_file(blackrecord, &client_data);
			rewind(Ptr_2);
		}
		fclose(Ptr);
		fclose(Ptr_2);
		fclose(blackrecord);
	}
}
