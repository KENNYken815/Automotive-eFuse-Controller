CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Ifirmware/inc
SRC=firmware/src/efuse.c firmware/src/main.c
all: efuse_demo
efuse_demo: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@
clean:
	rm -f efuse_demo
.PHONY: all clean
