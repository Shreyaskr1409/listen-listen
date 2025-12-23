#pragma once

#include "glib.h"
#include "gst/gstelement.h"

typedef struct __PlaybackController {
    GstElement *playbin;
    char       *current_uri;
    GstState    current_state;
    char      **upcoming_uri;  // array of strings (playlist)
    gboolean    has_next;

    gint64   duration;  // in nanoseconds
    gint64   position;  // in nanoseconds
    gboolean buffering;
    gdouble  volume;

    GMutex lock;  // protects this struct while multithreading
    GCond  cond;  // this is like channels in golang

    GstBus  *bus;
    GThread *bus_thread;
    gboolean bus_thread_running;

    void (*track_finished_cb)(const char *last_track, const char *next_track);
    void (*error_cb)(const char *msg);
} PlaybackController;

GstElement *create_idle_playbin();
void        playback_controller_init(PlaybackController *ctl);
void        playback_controller_clear(PlaybackController *ctl);
void        controller_play_track(PlaybackController *ctl, char *uri);
void        controller_pause_track(PlaybackController *ctl);
void        controller_resume_track(PlaybackController *ctl);
void        controller_queue_next_track(PlaybackController *ctl, char *uri);
