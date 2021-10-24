#include "logic_test.h"

void write_data_to_file(FILE *ofPTR, Data Client) {
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
			&Client.number,
			Client.name,
			Client.surname,
			Client.addres,
			Client.tel_number,
			&Client.indebtedness,
			&Client.credit_limit,
			&Client.cash_payments) != -1) {
		fprintf(ofPTR, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
			Client.number,
			Client.name,
			Client.surname,
			Client.addres,
			Client.tel_number,
			Client.indebtedness,
			Client.credit_limit,
			Client.cash_payments);
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
}

void transaction_write(FILE *ofPTR, Data transfer) {
	printf("%s\n%s\n",
		"1 Number account: ",
		"2 Client cash payments: ");
	while (scanf("%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
		fprintf(ofPTR, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
		printf("%s\n%s\n",
			"1 Number account:",
			"2 Client cash payments: ");
	}
}

void write_transfer_to_file(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer) {
	while (fscanf(ofPTR, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
		&client_data.number,
		client_data.name,
		client_data.surname,
		client_data.addres,
		client_data.tel_number,
		&client_data.indebtedness,
		&client_data.credit_limit,
		&client_data.cash_payments) != -1) {
		while (fscanf(ofPTR_2, "%3d%6lf", &transfer.number, &transfer.cash_payments) != -1) {
			if (client_data.number == transfer.number && transfer.cash_payments != 0) {
				client_data.credit_limit += transfer.cash_payments;
			}
		}
		fprintf(blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2lf%12.2lf%12.2lf\n",
			client_data.number,
			client_data.name,
			client_data.surname,
			client_data.addres,
			client_data.tel_number,
			client_data.indebtedness,
			client_data.credit_limit,
			client_data.cash_payments);
		rewind(ofPTR_2);
	}
}
