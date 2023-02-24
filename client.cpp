#include <QApplication>
#include "Interface/window.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>


int port;

int main(int argc, char *argv[]) {
    QApplication a(argc,argv);
    //Create interface window
    Window w;
    //Create server descriptor and connect to it
    int sd;
    struct sockaddr_in server;
    if (argc != 3) {
        printf("[client] Syntax: %s <server_address> <port>\n", argv[0]);
        return -1;
    }

    port = atoi(argv[2]);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("[client]Error when creating socket\n");
        return errno;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("[client]Error when connecting to server\n");
        return errno;
    }
    w.setSocketDescriptor(sd);
    a.exec();
    int option = 12;
    int nrBytes = send(sd,&option,sizeof(int),MSG_NOSIGNAL);
    close(sd);
    return 0;
}