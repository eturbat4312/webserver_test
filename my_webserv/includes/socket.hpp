#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <exception>
#include <algorithm>
#include <sstream>
#include "fcntl.h"

#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <cstring>

class Socket
{
	private:
		int _socket_server_fd;
		int _socket_client_fd;
		int _port;
		std::string _host;
		struct sockaddr_in _address;

		void *_buffer;

	public:
		Socket();
		Socket(int port, std::string host);
		~Socket();

		int get_socket_fd();
		int get_port();
		std::string get_host();
		struct sockaddr_in get_address();

		void set_socket_fd(int socket_fd);
		void set_port(int port);
		void set_host(std::string host);
		void set_address(struct sockaddr_in address);

		int socket_fd();
		int address_socket();
		int	bind_socket();
		int	listen_socket();
		int start_server();

		int accept_connection(); //returns new socket
		int read_socket(); //returns valread
		// int write_socket(std::string str); //returns valread
		int send_response(std::string str); //returns valread
		int close_socket_client();
		int close_socket_server();

		int poll_socket();
		int poll_loop();
};
