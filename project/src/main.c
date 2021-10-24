#include "logic_test.h"

#define TEXT_PRINT "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n"
#define DATA_WRITE 1
#define TRANSACTION 2
#define TRANSFER_WRITE 3

int main(void) {
	int choice = 0;
	printf("%s", TEXT_PRINT);
	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case DATA_WRITE:
				write_data_to_file();
				break;
			case TRANSACTION:
				transaction_write();
				break;
			case TRANSFER_WRITE:
				write_transfer_to_file();
				break;
			default:
				puts("error");
				break;
		}
		printf("%s", TEXT_PRINT);
	}
    return 0;
}
