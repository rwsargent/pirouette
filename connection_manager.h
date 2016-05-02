#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H
#include "socket_layer.h"

#include <thread>
#include <vector>
#include <mutex>

#define MAX_CONNECTIONS 4


void init_connections();
void establish_connection(int socket_fd);
#endif
