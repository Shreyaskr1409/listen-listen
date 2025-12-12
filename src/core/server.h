#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <asm-generic/socket.h>
#include "controller.h"

#define PORT 4545
#define BUFFER_SIZE 1024

void run_server(PlaybackController *ctl);
