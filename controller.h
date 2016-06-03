#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "socket_layer.h"
#include "servo.h"
#include "connection_manager.h"

#include <iostream>
#include <memory>

typedef struct Client {
  int socketfd;
} Client;

void listen_for_commands(std::unique_ptr<Client>);

#endif
