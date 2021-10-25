#include "input_output_test.h"

void write_to_file(FILE *datafile, Data *data) {
    fprintf(datafile, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
		data->number,
		data->name,
		data->surname,
		data->addres,
		data->tel_number,
		data->indebtedness,
		data->credit_limit,
		data->cash_payments);
}

int read_from_file(FILE *datafile, Data *data) {
	return fscanf(datafile, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
		&data->number,
		data->name,
		data->surname,
		data->addres,
		data->tel_number,
		&data->indebtedness,
		&data->credit_limit,
		&data->cash_payments);
}
