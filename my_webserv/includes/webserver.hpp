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


};