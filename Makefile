TARGET = ./main.out
TEST_TARGET = ./test_main.out
HDRS_DIR = project/include

SRCS = \
		project/src/main.c \
		project/src/logic_test.c 

TEST_SRCS = \
		project/src/io_test_main.c \
		project/src/input_output_test.c

.PHONY: all build rebuild check test memtest clean

all: clean check test memtest rectest

$(TARGET): $(SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TEST_TARGET): $(TEST_SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TEST_TARGET) $(CFLAGS) $(TEST_SRCS)

build: $(TARGET) $(TEST_TARGET)

rebuild: clean build

check:
	./linters/run.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

rectest: $(TEST_TARGET)
	./test_main.out

clean:
	rm -rf $(TARGET) $(TEST_TARGET) *.dat
