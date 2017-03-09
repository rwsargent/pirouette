/*
 * The main controlling logic of pirouette
 */
#include "controller.h"
void listen_for_commands(std::unique_ptr<Client> client) {
  while(true) {
    auto message = socket_receive(client->socketfd);
    if(message.empty()) {
      std::cout << "Connection ended." << std::endl;
      return;//break;
    }
    for(auto token : explode(message, '\n')) {
        if(token.find("LEFT") == 0) {
          turn_left();
        } else if (token.find("RIGHT") == 0) {
          turn_right();
        } else if (token.find("STOP") == 0) {
          stop();
          break; // leave this current string of commands. If i get a stop I want to stop completely.
        } else if(token.find("DISCONNECT") == 0) {
          return;
        } else if(token.find("AGAIN") ==0) {
          continue;
        }
      }
  }
  // remove_thread(std::this_thread::get_id()); not necessary for single connection
}

const vector<string> explode(const string& s, const char& c)
{
  string buff{""};
  vector<string> v;

  for(auto n:s)
  {
    if(n != c) buff+=n; else
      if(n == c && buff != "") { v.push_back(buff); buff = ""; }
  }
  if(buff != "") v.push_back(buff);

  return v;
}
