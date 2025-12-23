#include "server.h"

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "controller.h"
#include "utils.h"

typedef struct __Connection {
    int                sockfd;
    struct sockaddr_in addr;  // comes from netinet/in.h (requires sys/socket.h)
    socklen_t          addr_len;
} Connection;

typedef struct __HandleClientArgs {
    Connection *conn;
    PlaybackController *ctl;
} HandleClientArgs;

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
    printf("------------\n");

    while (utl_global->shutdown_req == 0) {
        Connection *client_conn = malloc(sizeof(*client_conn));
        client_conn->addr_len = sizeof(client_conn->addr);

        // accept is going to block till a connection is made
        // OR
        // till the socket is closed
        // (thus in case of shutdown, the server socket needs to be closed)
        client_conn->sockfd = accept(server_conn->sockfd, (struct sockaddr *)&client_conn->addr,
                                     &client_conn->addr_len);

        if (client_conn->sockfd < 0) {
            if (utl_global->shutdown_req == 0) perror("Accept failed");
            close(client_conn->sockfd);
            free(client_conn);
            continue;
        }

        printf("INFO: Request recieved.\n");

        HandleClientArgs* args = malloc(sizeof(HandleClientArgs));
        *args = (HandleClientArgs) {
            client_conn,
            ctl
        };

        pthread_t worker_thread;
        pthread_create(&worker_thread, NULL, handle_client, (void *)args);
        // remember to make the handle_client have a timeout later
        pthread_detach(worker_thread);
    }
}

void *handle_client(void *arg) {
    HandleClientArgs *args = (HandleClientArgs *)arg;

    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes_received = recv(args->conn->sockfd, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    char *saveptr = NULL;
    char *token = strtok_r(buffer, " ", &saveptr);

    printf("%s\n", token);

    if (strcmp(token, "Play") == 0) {
        printf("SUCCESS\n");
        controller_play_track(args->ctl, "nothing");
    } else {
        printf("FAILURE %s\n", token);
    }

    send(args->conn->sockfd, buffer, bytes_received, 0);

    printf("%d\n", close(args->conn->sockfd));
    free(args->conn);
    free(args);
    printf("------------\n");

    return NULL;
}
