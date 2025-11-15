CC    = gcc
CFLAG = -Wall -g
BUILD = build

test:
	$(CC) $(CFLAG) /test/test.c -o $(BUILD)/test
