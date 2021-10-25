#include "logic_test.h"

#define PRINT_ACTIONS() printf("%s", \
	"please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n")
#define DATA_WRITE 1
#define TRANSACTION 2
#define TRANSFER_WRITE 3
#define RECORD_FILE "record.dat"
#define TRANSACTION_FILE "transaction.dat"
#define BLACKRECORD_FILE "blackrecord.dat"

int main(void) {
	int choice = 0;
	PRINT_ACTIONS();
	while (scanf("%d", &choice) != -1) {
		switch(choice) {
			case DATA_WRITE:
				write_data_to_file(RECORD_FILE);
				break;
			case TRANSACTION:
				transaction_write(TRANSACTION_FILE);
				break;
			case TRANSFER_WRITE:
				write_transfer_to_file(RECORD_FILE, TRANSACTION_FILE, BLACKRECORD_FILE);
				break;
			default:
				puts("error");
				break;
		}
		PRINT_ACTIONS();
	}
    return 0;
}
