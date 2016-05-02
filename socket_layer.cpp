/** Author: Ryan Sargent
 *  This closely follows Beej's Networking guide <https://beej.us/guide/bgnet/> to set up a socket, 
 *  and listen on said socket. 
 */
#include "socket_layer.h"

void sigchld_handler(int s) {
  // waitpid() might overwrite errno, so we save and restore it:
  int saved_errno = errno;

  while(waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int init_server_socket() {
	struct addrinfo hints, *servinfo, *p;
	int server_sock_fd, rv;
	int yes=1;
	struct sigaction sa;
	memset(&hints, 0, sizeof(hints));
  
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((server_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(server_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(server_sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(server_sock_fd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

  if (p == NULL)  {
    fprintf(stderr, "server: failed to bind\n");
    exit(1);
  }

	if (listen(server_sock_fd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("server: waiting for connections...\n");
	return server_sock_fd;
}

int socket_accept(int listener_socket_fd) {
	int connectors_fd;
	struct sockaddr_storage their_addr; // connector's address information
  socklen_t sin_size;
	char s[INET6_ADDRSTRLEN];
	
	sin_size = sizeof their_addr;
	connectors_fd = accept(listener_socket_fd, (struct sockaddr *)&their_addr, &sin_size);
	if (connectors_fd == -1) {
		perror("accept");
		return -1;
	}

	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
	printf("server: got connection from %s\n", s);
	return connectors_fd;
}

void socket_send(int sockfd, std::string message) {
  int len, bytes_sent;
  len = message.size() + 1;
  char* socket_message = new char[len];
  std::copy(str.being(), str.end(), socket_message);
  do {
    bytes_sent = send(sockfd, socket_message, len, 0);
    len -= bytes_sent;
    socket+message += bytes_sent; // move pointer number of bytes sent
  } while (len);
  delete socket_message;
}

std::string socket_receive(int sockfd) {
  char buffer[MAXDATASIZE];
  int num_bytes = 0;
  if ((num_bytes = recv(sockfd, buffer, MAXDATASIZE-1, 0)) == -1) {
    return std::string(); // empty string, nothing recieved
  }
  if (errno == EAGAIN || errno == EWOULDBLOCK) {
    return std::string();
  }
  buffer[num_bytes] = '\0';
  std::string message = std::string(buffer);
  return message;
}
