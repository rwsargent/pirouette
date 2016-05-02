/**
 *  Author: Ryan Sargent
 *  Piourette is an app to control a spinning camera. 
 *
 */
#include "pirouette.h"

using namespace std;

atomic_bool running;

void accept_connections(int);

int main(int argc, char** argv) {
  thread accept_thread;
  running = true;

  //init something to do with GPIO
	init_GPIO();

  //init thread control?
  
	int server_socket_fd;
	server_socket_fd = init_server_socket();

  accept_thread = thread(accept_connections, server_socket_fd);
  
  while(1) {  // main accept() loop
    
  }

  return 0;
}

void accept_connections(int listen_socket_fd) {
  int connection_socket_fd = -1;
  struct timeval timeval;
  timeval.tv_sec = 5; // 5 second timeout
  timeval.tv_usec = 0; // microseconds. zero, but initing to avoid weird bugs.
  while(running) {
    connection_socket_fd = socket_accept(listen_socket_fd);
    if(connection_socket_fd == -1) { 
      continue; // error in accepting
    }
    setsockopt(connection_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeval, sizeof(struct timeval));
    string connection_message = socket_receive(connection_socket_fd);
    if(!connection_message.empty()) {
      establish_connection(connection_socket_fd);
    }
  }
}
