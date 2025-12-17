# Listen Listen
A TUI and GUI music player built with C core and Go for TUI.

The basic plan is to have the C core which will utilize the gstreamer utility to play music.
The C program will also open a socket for the GUI and TUI to communicate through. Through
these sockets, the TUI and GUI will control music playback. Hopefully this turns out to
be an amazing project and teaches me a lot of stuff.

## TODO
- implement graceful shutdown
