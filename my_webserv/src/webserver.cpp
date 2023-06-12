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

// int webServer::poll_socket(Servers *server)
// {
// 	pollfd fd;
// 	fd.fd = server->socket_fd;
// 	fd.events = POLLIN;
// 	this->_fds.push_back(fd);
// 	return EXIT_SUCCESS;
// }

// int webServer::poll_loop()
// {
// 	poll_socket(&this->_serv_vector[0]);
// 	while (true)
// 	{
// 		int poll_count = poll(&this->_fds[0], this->_fds.size(), 1);
// 		if (poll_count < 0)
// 		{
// 			std::cerr << "Failed to poll sockets" << std::endl;
// 			return EXIT_FAILURE;
// 		}
// 		for (size_t i = 0; i < this->_fds.size(); i++)
// 		{
// 			if (this->_fds[i].revents & POLLIN) // POLLIN = There is data to read
// 			{
// 				if (this->_fds[i].fd == this->_serv_vector[i].socket_fd)
// 				{
// 					std::cout << "Accepting new connection" << std::endl;
// 					if (accept_connection(&this->_serv_vector[i]) == EXIT_FAILURE)
// 						return EXIT_FAILURE;
// 					// std::cout << "Reading from socket" << std::endl;
// 					// if (read_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
// 					// 	return EXIT_FAILURE;
// 					std::cout << "Writing to socket" << std::endl;
// 					if (write_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
// 						return EXIT_FAILURE;
// 					std::cout << "Closing socket" << std::endl;
// 					if (close_socket(&this->_serv_vector[i]) == EXIT_FAILURE)
// 						return EXIT_FAILURE;
// 				}
// 			}
// 		}
// 	}
// 	return EXIT_SUCCESS;
// }







