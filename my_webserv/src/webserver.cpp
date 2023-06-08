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

int webServer::socket_fd(Servers *server)
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (serverSocket == -1) {
		std::cerr << "Failed to create socket" << std::endl;
		return EXIT_FAILURE;
	}
	server->socket_fd = serverSocket;
	return EXIT_SUCCESS;
}


int webServer::address_socket(Servers *server)
{
	server->_address.sin_family = AF_INET;
	server->_address.sin_addr.s_addr = inet_addr(server->host.c_str());// need to check host assignment!!!
	server->_address.sin_port = htons(server->_port);
	memset(server->_address.sin_zero, '\0', sizeof(server->_address.sin_zero));
	return EXIT_SUCCESS;
}

int webServer::bind_socket(Servers *server)
{
	if (bind(server->socket_fd, (struct sockaddr*)&server->_address, sizeof(server->_address)) < 0) {
		std::cerr << "Failed to bind socket to address" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int webServer::listen_socket(Servers *server)
{
	if (listen(server->socket_fd, SOMAXCONN) < 0) {
		std::cerr << "Failed to listen for connections" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


int webServer::start_server()
{
	if (socket_fd(&this->_serv_vector[0]) == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (address_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (bind_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (listen_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int webServer::accept_connection(Servers *server)
{
	int clientSocket;
	sockaddr_in clientAddress{};
	socklen_t clientAddressLength = sizeof(clientAddress);
	clientSocket = accept(server->socket_fd, (struct sockaddr*)&clientAddress, &clientAddressLength);
	if (clientSocket < 0) {
		std::cerr << "Failed to accept connection" << std::endl;
		return EXIT_FAILURE;
	}
	server->new_socket = clientSocket;
	return EXIT_SUCCESS;
}

int webServer::read_socket(Servers *server)
{
	int valread = read(server->new_socket, server->buffer, 1024);
	std::cout << "buffer: " << server->buffer << std::endl;
	std::cout << "new_socket: " << server->new_socket << std::endl;
	std::cout << "valread: " << valread << std::endl;
	if (valread < 0)
	{
		std::cerr << "Failed to read from socket" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int webServer::write_socket(Servers *server)
{
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	int valsend = send(server->new_socket, hello.c_str(), hello.length(), 0);
	if (valsend < 0)
	{
		std::cerr << "Failed to send message" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int webServer::close_socket(Servers *server)
{
	close(server->new_socket);
	return EXIT_SUCCESS;
}

int webServer::poll_socket(Servers *server)
{
	pollfd fd;
	fd.fd = server->socket_fd;
	fd.events = POLLIN;
	this->_fds.push_back(fd);
	return EXIT_SUCCESS;
}

int webServer::poll_loop()
{
	std::cout << "poll init" << std::endl;
	if (poll_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
		return EXIT_FAILURE;

	std::cout << "poll loop" << std::endl;
	while (true)
	{
		std::cout << "accept_connection" << std::endl;
		if (accept_connection(&this->_serv_vector[0]) == EXIT_FAILURE)
			return EXIT_FAILURE;
		std::cout << "read_socket" << std::endl;
		if (read_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
			return EXIT_FAILURE;
		std::cout << "write_socket" << std::endl;
		if (write_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
			return EXIT_FAILURE;
		std::cout << "close_socket" << std::endl;
		if (close_socket(&this->_serv_vector[0]) == EXIT_FAILURE)
			return EXIT_FAILURE;

		// int poll_count = poll(&this->_fds[0], this->_fds.size(), -1);
		// std::cout << "poll_count: " << poll_count << std::endl;
		// if (poll_count < 0)
		// {
		// 	std::cerr << "Failed to poll sockets" << std::endl;
		// 	return EXIT_FAILURE;
		// }
		// for (size_t i = 0; i < this->_fds.size(); i++)
		// {
		// 	if (this->_fds[i].revents & POLLIN)
		// 	{
		// 		if (this->_fds[i].fd == this->_serv_vector[i].socket_fd)
		// 		{
		// 			std::cout << "i : " << i << std::endl;
		// 			if (accept_connection(&this->_serv_vector[i]) == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 			if (read_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 			if (write_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 			if (close_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
		// 				return EXIT_FAILURE;
		// 		}
		// 	}
		// }
	}
	return EXIT_SUCCESS;
}







