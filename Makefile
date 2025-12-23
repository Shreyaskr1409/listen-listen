CC    = gcc
CFLAG = -Wall -g
BUILD = build
GSTRF = `pkg-config --cflags --libs gstreamer-1.0`
FILES = src/daemon/utils.c src/daemon/controller.c src/daemon/server.c src/daemon/main.c

build-server:
	$(CC) $(CFLAG) $(FILES) -o $(BUILD)/gst-server $(GSTRF)
	$(BUILD)/gst-server

test:
	$(CC) $(CFLAG) tests/test.c -o $(BUILD)/test $(GSTRF)
	$(BUILD)/test

clean:
	rm -r $(BUILD)
	mkdir $(BUILD)
	touch $(BUILD)/.gitkeep

.PHONY: test clean
