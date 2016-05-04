#include "connection_manager.h"

using namespace std;

vector<thread> connections;
mutex connection_mutex;

bool roomForConnections() {
  return connections.size() < MAX_CONNECTIONS;
}

void init_connections() {
  connections.reserve(MAX_CONNECTIONS);
}

void establish_connection(int socket_fd) {
  connection_mutex.lock();
  if(!roomForConnections()) {
    socket_send(socket_fd, "At Max Connections\n");
    return;
  }
  socket_send(socket_fd, "Accepted\n");
//  connections.push_back(
  connection_mutex.unlock();
}
