#pragma once

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

typedef struct __program_utils {
    volatile sig_atomic_t shutdown_req;
    struct sigaction      sa;

    int sockfd;
    int connfd;

    pthread_t server_thread;
} program_utils;

extern program_utils *utl_global;

void           handle_sig(int sig);
program_utils *program_utils_create();
void           program_utils_clear(program_utils *utl);
