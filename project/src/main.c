#include "parser.h"


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_eml = argv[1];
    data_t *eml_data = create_data();
    if (get_eml(path_to_eml, eml_data) == -1) {
        free_data(eml_data);
        return -1;
    }
    if (eml_data->bound_size == 0 && eml_data->parts_count == 0) {
        eml_data->parts_count = 1;
    }
    printf("%s|%s|%s|%zu", eml_data->from, eml_data->to, eml_data->date, eml_data->parts_count);
    free_data(eml_data);
    return 0;
}
