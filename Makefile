CC    = gcc
CFLAG = -Wall -g
BUILD = build
GSTRF = `pkg-config --cflags --libs gstreamer-1.0`
LDFLAGS = -Ldeps/lib -lraylib -lGL -lm -lpthread -ldl -lrt

FILES_DAEMON = src/daemon/utils.c src/daemon/controller.c src/daemon/server.c src/daemon/main.c
FILES_GUI = src/gui/main.c

build-gui:
	$(CC) $(CFLAG) $(FILES_GUI) $(LDFLAGS) -o $(BUILD)/listen-gui
	$(BUILD)/listen-gui

build-server:
	$(CC) $(CFLAG) $(FILES_DAEMON) -o $(BUILD)/gst-server $(GSTRF)
	$(BUILD)/gst-server

test:
	$(CC) $(CFLAG) tests/test.c -o $(BUILD)/test $(GSTRF)
	$(BUILD)/test

setup-raylib:
	cd deps/raylib/src/ && make clean && make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=TRUE && \
		cp libraylib.a ../../lib/libraylib.a && cp raylib.h ../../include/raylib.h

clean:
	rm -r $(BUILD)
	mkdir $(BUILD)
	touch $(BUILD)/.gitkeep

.PHONY: test clean
