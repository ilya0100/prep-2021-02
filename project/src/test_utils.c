#include "main_module.h"

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
}
