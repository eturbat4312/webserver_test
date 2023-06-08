#include "../includes/webserver.hpp"

webServer::webServer(std::vector<Servers> servers){
	this->_servers = servers;
	this->_serv_vector = servers;
	// for (size_t i = 0; i < servers.size(); i++)
	// {
	// 	for (size_t j = 0; j < servers[i].port.size(); j++)
	// 	{
	// 		Servers _servers = servers[i];
	// 		_servers._port = servers[i].port[j];
	// 		std::cout << "_servers._port: " << _servers._port << std::endl;
	// 		_servers._address.sin_family = AF_INET;
	// 		_servers._address.sin_addr.s_addr = inet_addr(servers[i].host.c_str());// need to check host assignment!!!
	// 		_servers._address.sin_port = htons(servers[i].port[j]);
	// 		memset(_servers._address.sin_zero, '\0', sizeof(_servers._address.sin_zero));
	// 		this->_serv_vector.push_back(_servers);
	// 	}
	// }
}

webServer::~webServer(){}

int webServer::socket_fd()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
		if (serverSocket == -1) {
			std::cerr << "Failed to create socket" << std::endl;
			// Handle error
			return EXIT_FAILURE;
		}
		this->_serv_vector[i].socket_fd = serverSocket;
	}
	return EXIT_SUCCESS;
}

int webServer::address_socket()
{
	std::cout << "port: " << this->_serv_vector[0]._port << std::endl;
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		sockaddr_in serverAddress; // Zero-intialize the address
		serverAddress.sin_family = AF_INET; // IPv4
		serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any address
		std::cout << "port: " << this->_serv_vector[i]._port << std::endl;
		serverAddress.sin_port = htons(this->_serv_vector[i]._port); // Replace with the desired port from the config
		this->_serv_vector[i]._address = serverAddress;
	}
	return EXIT_SUCCESS;
}

int webServer::bind_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		if (bind(_serv_vector[i].socket_fd, (struct sockaddr*)&this->_serv_vector[i]._address, sizeof(this->_serv_vector[i]._address)) < 0) {
			std::cerr << "Failed to bind socket to address" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int webServer::listen_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		if (listen(_serv_vector[i].socket_fd, SOMAXCONN) < 0) {
			std::cerr << "Failed to listen for connections" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int webServer::start_server()
{
	if (socket_fd() == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (address_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (bind_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (listen_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int webServer::accept_connection()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		int addrlen = sizeof(this->_serv_vector[i]._address);
		int new_socket = accept(this->_serv_vector[i].socket_fd, (struct sockaddr *)&this->_serv_vector[i]._address, (socklen_t*)&addrlen);
		if (new_socket < 0)
		{
			std::cerr << "Failed to accept connection" << std::endl;
			return EXIT_FAILURE;
		}
		this->_serv_vector[i].new_socket = new_socket; //line written by copilot byut no idea why
	}
	return EXIT_SUCCESS;
}

int webServer::read_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		int valread = read(this->_serv_vector[i].new_socket, this->_serv_vector[i].buffer, 1024);
		if (valread < 0)
		{
			std::cerr << "Failed to read from socket" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int webServer::write_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
		int valsend = send(this->_serv_vector[i].new_socket, hello.c_str(), hello.length(), 0);
		if (valsend < 0)
		{
			std::cerr << "Failed to send message" << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int webServer::close_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		close(this->_serv_vector[i].new_socket);
	}
	return EXIT_SUCCESS;
}

int webServer::poll_socket()
{
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		pollfd fd;
		fd.fd = this->_serv_vector[i].socket_fd;
		fd.events = POLLIN;
		this->_fds.push_back(fd);
	}
	return EXIT_SUCCESS;
}

int webServer::poll_loop()
{
	while (true)
	{
		std::cout << "poll_loop" << std::endl;
		accept_connection();
		write_socket();
		// int poll_count = poll(&this->_fds[0], this->_fds.size(), -1);
		// if (poll_count < 0)
		// {
		// 	std::cerr << "Failed to poll sockets" << std::endl;
		// 	return EXIT_FAILURE;
		// }
		// std::cout << "poll_count: " << poll_count << std::endl;
		// for (size_t i = 0; i < this->_fds.size(); i++)
		// {
		// 	if (this->_fds[i].revents & POLLIN)
		// 	{
		// 		if (this->_fds[i].fd == this->_serv_vector[i].socket_fd)
		// 		{
		// 			if (accept_connection() == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 		}
		// 		else
		// 		{
		// 			if (read_socket() == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 			if (write_socket() == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 			if (close_socket() == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 		}
		// 	}
		// }
	}
	return EXIT_SUCCESS;
}







