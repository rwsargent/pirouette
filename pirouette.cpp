/**
 *  Author: Ryan Sargent
 *  Piourette is an app to control a spinning camera. 
 *
 */
#include "pirouette.h"
#define TIMEOUT 0
using namespace std;

atomic_bool running;
int server_socket_fd; // shut down listening port.

void shutdown(int signal);
void assignSignalHandlers();
void accept_connections(int);

int main(int argc, char** argv) {
  thread accept_thread;
  running = true;

  //init something to do with GPIO
	init_GPIO();
  assignSignalHandlers();
  
  //init thread control?
	server_socket_fd = init_server_socket();
    
  accept_thread = thread(accept_connections, server_socket_fd);
  accept_thread.join();
  return 0;
}

void accept_connections(int listen_socket_fd) {
  int connection_socket_fd = -1;
  struct timeval timeval;
  #ifdef TIMEOUT
  timeval.tv_sec = 5; // 5 second timeout
  timeval.tv_usec = 0; // microseconds. zero, but initing to avoid weird bugs.
  #endif 
  while(running) {
    connection_socket_fd = socket_accept(listen_socket_fd);
    if(connection_socket_fd == -1) { 
      continue; // error in accepting
    }
    #ifdef TIMEOUT
    setsockopt(connection_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeval, sizeof(struct timeval));
    #endif
    string connection_message = socket_receive(connection_socket_fd);
    cout << "Connection message: " << connection_message << endl;
    if(!connection_message.empty()) {
      establish_connection(connection_socket_fd);
    }
  }
}

void assignSignalHandlers() {
  (void)signal(SIGINT, shutdown);
  (void)signal(SIGQUIT, shutdown);
  (void)signal(SIGTERM, shutdown);
}

void shutdown(int signal) {
  cout << "Shutting down" << endl;
  close_socket(server_socket_fd);
  close_servo();
  exit(0);
}
