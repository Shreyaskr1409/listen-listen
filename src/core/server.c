#include "server.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "controller.h"

typedef struct __Connection {
    int                sockfd;
    int                connfd;
    struct sockaddr_in addr;  // comes from netinet/in.h (requires sys/socket.h)
    socklen_t          addr_len;
} Connection;

static void handle_conn(PlaybackController *ctl, Connection *conn);

void run_server(PlaybackController *ctl) {
    Connection conn;

    conn.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn.sockfd < 0) {
        perror("Error while creating the socket");
        return;
    }

    // in case program is restarted after a crash
    // bypasses the waiting time for the socket to become reusable
    int opt = 1;
    setsockopt(conn.sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    conn.addr.sin_family = AF_INET;
    conn.addr.sin_addr.s_addr = INADDR_ANY;
    conn.addr.sin_port = htons(PORT);

    if (bind(conn.sockfd, (struct sockaddr *)&conn.addr, sizeof(conn.addr)) != 0) {
        perror("error while binding to the socket");
        close(conn.sockfd);  // comes from unistd.h
        return;
    }

    handle_conn(ctl, &conn);

    close(conn.sockfd);
    return;
}

static void handle_conn(PlaybackController *ctl, Connection *conn) {
    // Should first prepare the gst pipeline, put it in the PAUSED state
    // and then listen to connections

    if (listen(conn->sockfd, 4)) {
        perror("error while listening to the socket");
        return;
    }

    printf("Server listening on port %d...\n", PORT);
}
