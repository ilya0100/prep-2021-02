#include "prime.h"
#include "series_of_numbers.h"
#include "utils.h"


#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_ROW_IMPL    4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int Test_case = atoi(argv[1]);
    const char* data;
    data = argv[2];

    switch (Test_case) {
        case TST_FOO_FIX: {
            int to = atoi(data);
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                int base = atoi(data);
                int pow = atoi(argv[3]);
                int res = custom_pow(base, pow);
                printf("%d\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
            int num = atoi(data);
            int res = is_prime(num);
            printf("%d\n", res);
            break;
        }
        case TST_ROW_IMPL: {
            int num = atoi(data);
            series_of_num(num);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
