TARGET = ./main.out
VALGRIND_LOG = "valgrind.log"

HDRS = \
		project/include

SRCS = \
		project/src/main.c \
		project/src/parser.c

.PHONY: all check build test memtest rebuild clean

all: clean check build test memtest

check:
	./run_linters.sh

build: $(TARGET)

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

rebuild: clean build

$(TARGET): $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -f $(TARGET) ${VALGRIND_LOG}