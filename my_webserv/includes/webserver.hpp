#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <cstring>

#include "config.hpp"


class Servers;

class	webServer{
private:
	std::vector<Servers> _servers;
	std::vector<pollfd> _fds;
	std::vector<Servers> _serv_vector;

public:
	webServer(std::vector<Servers> servers);
	~webServer();

	int socket_fd();
	int address_socket();
	int	bind_socket();
	int	listen_socket();
	int start_server();

	int accept_connection();
	int read_socket();
	int write_socket();
	int close_socket();

	int poll_socket();
	int poll_loop();

	// int get_max_fd();
	// int get_fd(int i);
	// int get_socket_fd(int i);
	// int get_new_socket(int i);
	// int get_port(int i);
	// std::string get_host(int i);
	// std::string get_root(int i);
	// std::string get_returned(int i);
	// std::string get_index(int i);
	// std::vector<std::string> get_server_name(int i);
	// std::vector<Locations> get_locations(int i);
	// std::vector<errorPages> get_error_page(int i);
	// long get_client_body_size(int i);

};