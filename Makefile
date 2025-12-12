CC    = gcc
CFLAG = -Wall -g
BUILD = build
GSTRF = `pkg-config --cflags --libs gstreamer-1.0`

build-server:
	$(CC) $(CFLAG) src/core/main.c -o $(BUILD)/gst-server $(GSTRF)
	$(BUILD)/gst-server

test:
	$(CC) $(CFLAG) tests/test.c -o $(BUILD)/test $(GSTRF)
	$(BUILD)/test

clean:
	rm -r $(BUILD)
	mkdir $(BUILD)
	touch $(BUILD)/.gitkeep

.PHONY: test clean
