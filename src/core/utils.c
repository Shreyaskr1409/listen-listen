#include "utils.h"
#include <signal.h>
#include <unistd.h>

program_utils *program_utils_create() {
    utl_global = (program_utils *)calloc(1, sizeof(*utl_global));
    if (!utl_global) return NULL;

    utl_global->shutdown_req = 0;
    utl_global->sockfd = 0;
    utl_global->connfd = 0;

    utl_global->sa = (struct sigaction){
        .sa_handler = handle_sig
    };

    // clears sa_mask from containing garbage value
    sigemptyset(&utl_global->sa.sa_mask);
    sigaction(SIGINT, &utl_global->sa, NULL);
    sigaction(SIGTERM, &utl_global->sa, NULL);

    return utl_global;
}

void handle_sig(int sig) {
    utl_global->shutdown_req = 1;
    close(utl_global->sockfd);
    close(utl_global->connfd);

    // next step would be to join threads
}
