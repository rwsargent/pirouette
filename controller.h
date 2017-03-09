#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "socket_layer.h"
#include "servo.h"
#include "connection_manager.h"

#include <iostream>
#include <memory>
#include <vector>
typedef struct Client {
  int socketfd;
} Client;

using namespace std;

void listen_for_commands(std::unique_ptr<Client>);
const vector<string> explode(const string& input, const char& delim);
  
#endif
