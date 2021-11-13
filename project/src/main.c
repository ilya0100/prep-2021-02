#include "parser.h"


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_eml = argv[1];
    data_t eml_data = {0};
    if (get_eml(path_to_eml, &eml_data) == -1) {
        printf("Error\n");
    }
    printf("%s|%s|%s|%zu", eml_data.from, eml_data.to, eml_data.date, eml_data.parts_count);
    return 0;
}
