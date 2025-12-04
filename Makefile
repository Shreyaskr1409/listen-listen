CC    = gcc
CFLAG = -Wall -g
BUILD = build
GSTRF = `pkg-config --cflags --libs gstreamer-1.0`

test:
	$(CC) $(CFLAG) tests/test.c -o $(BUILD)/test $(GSTRF)
	$(BUILD)/test

clean:
	rm -r $(BUILD)
	mkdir $(BUILD)
	touch $(BUILD)/.gitkeep

.PHONY: test clean
