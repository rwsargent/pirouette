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
  unique_ptr<Client> newClient(new Client);
  newClient->socketfd = socket_fd;
  connections.push_back(thread(listen_for_commands, std::move(newClient)));
  connections.back().detach();
  connection_mutex.unlock();
}

void remove_thread(thread::id thread_id) {
  connection_mutex.lock();
  auto it = remove_if(connections.begin(), connections.end(), [thread_id](auto& it_thread) {
      return it_thread.get_id() == thread_id;
    });
  connections.erase(it, connections.end());
  connection_mutex.lock();
}
