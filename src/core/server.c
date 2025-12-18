#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "controller.h"
#include "utils.h"

typedef struct __Connection {
    int                sockfd;
    struct sockaddr_in addr;  // comes from netinet/in.h (requires sys/socket.h)
    socklen_t          addr_len;
} Connection;

static void handle_conn(PlaybackController *ctl, Connection *server_conn);

void run_server(PlaybackController *ctl) {
    Connection server_conn;

    server_conn.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_conn.sockfd < 0) {
        perror("Error while creating the socket");
        return;
    }

    // in case program is restarted after a crash
    // bypasses the waiting time for the socket to become reusable
    int opt = 1;
    setsockopt(server_conn.sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_conn.addr.sin_family = AF_INET;
    server_conn.addr.sin_addr.s_addr = INADDR_ANY;
    server_conn.addr.sin_port = htons(PORT);

    server_conn.addr_len = sizeof(server_conn.addr);

    if (bind(server_conn.sockfd, (struct sockaddr *)&server_conn.addr, server_conn.addr_len) != 0) {
        perror("error while binding to the socket");
        close(server_conn.sockfd);  // comes from unistd.h
        return;
    }

    // keep in mind
    utl_global->sockfd = server_conn.sockfd;

    handle_conn(ctl, &server_conn);

    if (utl_global->sockfd > 0) {
        close(server_conn.sockfd);
    }
    return;
}

static void handle_conn(PlaybackController *ctl, Connection *server_conn) {
    // Should first prepare the gst pipeline, put it in the PAUSED state
    // and then listen to connections

    if (listen(server_conn->sockfd, 4)) {
        perror("error while listening to the socket");
        return;
    }

    printf("Server listening on port %d...\n", PORT);

    while (utl_global->shutdown_req == 0) {
        Connection *client_conn = malloc(sizeof(*client_conn));
        client_conn->addr_len = sizeof(client_conn->addr);

        // accept is going to block till a connection is made
        // OR
        // till the socket is closed
        // (thus in case of shutdown, the server socket needs to be closed)
        client_conn->sockfd = accept(server_conn->sockfd,
                (struct sockaddr *)&client_conn->addr, &client_conn->addr_len);

        if (client_conn->sockfd < 0) {
            perror("Accept failed");
            close(client_conn->sockfd);
            free(client_conn);
            continue;
        }

        printf("Request recieved.\n");

        close(client_conn->sockfd);
        free(client_conn);
    }
}
