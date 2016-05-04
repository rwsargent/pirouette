#ifndef SOCKET_LAYER_H
#define SOCKET_LAYER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490"
#define BACKLOG 10     // how many pending connections queue will hold
#define MAXDATASIZE 512

int init_server_socket();
int socket_accept(int listener_socket_fd);
std::string socket_receive(int sockfd);
void socket_send(int sockfd, std::string message);
#endif
