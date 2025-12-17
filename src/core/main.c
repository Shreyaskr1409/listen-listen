#include <gstreamer-1.0/gst/gst.h>
#include <stdio.h>

#include "controller.h"
#include "utils.h"
#include "server.h"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int main(int argc, char *argv[]) {
    printf("Hello World\n");

    // here *utl = *utl_global
    program_utils *utl = program_utils_create();

    gst_init(&argc, &argv);

    PlaybackController ctl;
    playback_controller_init(&ctl);

    run_server(&ctl);

    program_utils_clear(utl);
    playback_controller_clear(&ctl);
    return 0;
}
