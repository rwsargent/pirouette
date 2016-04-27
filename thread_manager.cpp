#include "thread_manager.h"

using namespace std;

vector<thread> connections();
mutex connection_mutex;

void init_connections() {
  connections.reserve(MAX_CONNECTIONS);
}

void establish_connection(int socket_fd) {
  connection_mutex.lock();
  if(connections.size() < MAX_CONNECTIONS) {
    connections.push
  }
}


