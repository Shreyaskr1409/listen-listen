#include "utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

program_utils *utl_global = NULL;

program_utils *program_utils_create() {
    utl_global = (program_utils *)calloc(1, sizeof(*utl_global));
    if (!utl_global) return NULL;

    utl_global->shutdown_req = 0;
    utl_global->sockfd = -1;
    utl_global->connfd = -1;

    utl_global->sa = (struct sigaction){.sa_handler = handle_sig};

    // clears sa_mask from containing garbage value
    sigemptyset(&utl_global->sa.sa_mask);
    sigaction(SIGINT, &utl_global->sa, NULL);
    sigaction(SIGTERM, &utl_global->sa, NULL);

    return utl_global;
}

void handle_sig(int sig) {
    printf("Shutdown signal recieved");
    utl_global->shutdown_req = 1;
}

void program_utils_clear(program_utils *utl) {
    free(utl);
}
