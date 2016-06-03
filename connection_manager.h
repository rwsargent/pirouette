#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "socket_layer.h"
#include "controller.h"

#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <algorithm>

#define MAX_CONNECTIONS 4


void init_connections();
void establish_connection(int socket_fd);
void remove_thread(std::thread::id);
#endif
