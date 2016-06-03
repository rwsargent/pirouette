/*
 * The main controlling logic of pirouette
 */
#include "controller.h"

void listen_for_commands(std::unique_ptr<Client> client) {
  while(true) {
    auto message = socket_receive(client->socketfd);
    if(message.find("LEFT") == 0) {
      turn_left();
    } else if (message.find("RIGHT") == 0) {
      turn_right();
    } else if (message.find("STOP") == 0) {
      stop();
    } else if(message.find("DISCONNECT") == 0) {
      return;
    } else if(message.empty()) {
      std::cout << "Connection ended." << std::endl;
      break;
    } else if(message.find("AGAIN") ==0) {
      continue;
    }
  }
  remove_thread(std::this_thread::get_id());
}




