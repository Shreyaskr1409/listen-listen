#pragma once

#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "controller.h"

#define PORT 4545
#define BUFFER_SIZE 1024

struct __program_utils;

void  run_server(PlaybackController *ctl);
void *handle_client(void *arg);
