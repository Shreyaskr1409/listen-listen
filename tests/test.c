#include "glib.h"
#include "gst/gstbin.h"
#include "gst/gstelement.h"
#include "gst/gstelementfactory.h"
#include "gst/gstpipeline.h"
#include "gst/gstutils.h"
#include <gstreamer-1.0/gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

typedef struct _CustomData {
    GstElement *pipeline;
    GstElement *source;
    GstElement *convert;
    GstElement *resample;
    GstElement *sink;
} CustomData;

// Handler for the pad-added signal
static void pad_added_handler(GstElement *src, GstPad *pad, CustomData *customData);

int tutorial_main(int argc, char *argv[]) {
    CustomData data;
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;
    gboolean terminate = FALSE;

    gst_init(&argc, &argv);

    data.source = gst_element_factory_make("uridecodebin", "source");
    data.convert = gst_element_factory_make("audioconvert", "convert");
    data.resample = gst_element_factory_make("audioresample", "resample");
    data.sink = gst_element_factory_make("autoaudiosink", "sink");

    data.pipeline = gst_pipeline_new("test-pipeline");

    if (!data.pipeline || !data.source || !data.convert || !data.resample || !data.sink) {
        g_printerr("Not all elements could be created.\n");
        // free memory (skipped for the sake of tutorial)
        return -1;
    }
    
    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.convert, data.resample, data.sink, NULL);
    // here we can see that we are not linking source to the pipeline
    // this is because there are some elements which can not work unless they know what kind of data-
    // is provided to their src sink. Due to this reason, we are not joining the further filters to the src
    if (!gst_element_link_many(data.convert, data.resample, data.sink, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    g_object_set (data.source, "uri",
            "https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm",
            NULL);

    // TODO


    return 0;
}
