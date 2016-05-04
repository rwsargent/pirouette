/*
 * The main controlling logic of pirouette
 */
#include "controller.h"

void listen_for_commands(Client client) {
  auto message = socket_receive(client.socketfd);
}




