#include "../includes/webserver.hpp"

webServer::webServer(std::vector<Servers> servers){
	this->_servers = servers;
	for (size_t i = 0; i < servers.size(); i++)
	{
		for (size_t j = 0; j < servers[i].port.size(); j++)
		{
			Servers _servers = servers[i];
			_servers._port = servers[i].port[j];
			std::cout << "_servers._port: " << _servers._port << std::endl;
			_servers._address.sin_family = AF_INET;
			_servers._address.sin_addr.s_addr = inet_addr(servers[i].host.c_str());// need to check host assignment!!!
			_servers._address.sin_port = htons(servers[i].port[j]);
			memset(_servers._address.sin_zero, '\0', sizeof(_servers._address.sin_zero));
			this->_serv_vector.push_back(_servers);
		}
	}
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
	for (size_t i = 0; i < this->_serv_vector.size(); i++)
	{
		sockaddr_in serverAddress{}; // Zero-intialize the address
		serverAddress.sin_family = AF_INET; // IPv4
		serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any address
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

