#include <gstreamer-1.0/gst/gst.h>
#include <stdio.h>

#include "controller.h"
#include "server.h"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int main(int argc, char *argv[]) {
    printf("Hello World\n");

    PlaybackController ctl;
    run_server(&ctl);

    return 0;
}
