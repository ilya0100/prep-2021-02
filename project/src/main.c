#include "utils.h"
#include "logic_test.h"

#define FILENAME "transaction.dat"
#define DATA_WRITE 1
#define TRANSACTION 2
#define TRANSFER_WRITE 3

int main(void) {
	int choice = 0;
	FILE *Ptr, *Ptr_2, *blackrecord;
	Data client_data = {0}, transfer = {0};
	printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case DATA_WRITE:
				Ptr = fopen("record.dat", "r+");
				if(Ptr == NULL) {
					puts("Not acess");
				} else {
					write_data_to_file(Ptr, client_data);
					fclose(Ptr);
				}
				break;
			case TRANSACTION:
				Ptr = fopen(FILENAME, "r+");
				if(Ptr == NULL) {
					puts("Not acess");
				} else {
					transaction_write(Ptr, transfer);
					fclose(Ptr);
				}
				break;
			case TRANSFER_WRITE:
				Ptr = fopen("record.dat", "r");
				Ptr_2 = fopen("transaction.dat", "r");
				blackrecord = fopen("blackrecord.dat", "w");
				if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
					puts("exit");
				} else {
					write_transfer_to_file(Ptr, Ptr_2, blackrecord, client_data, transfer);
					fclose(Ptr);
					fclose(Ptr_2);
					fclose(blackrecord);
				}
				break;
			default:
				puts("error");
				break;
		}
		printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	}
    return 0;
}
