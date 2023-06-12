#include "../../includes/socket.hpp"

#define BUFFER_SIZE 1024

Socket::Socket(){}

Socket::Socket(int port, std::string host){
	this->_port = port;
	this->_host = host;
}

Socket::~Socket(){}

int Socket::get_socket_fd(){
	return this->_socket_server_fd;
}

int Socket::get_port(){
	return this->_port;
}

std::string Socket::get_host(){
	return this->_host;
}

struct sockaddr_in Socket::get_address(){
	return this->_address;
}

void Socket::set_socket_fd(int socket_fd){
	this->_socket_server_fd = socket_fd;
}

void Socket::set_port(int port){
	this->_port = port;
}

void Socket::set_host(std::string host){
	this->_host = host;
}

void Socket::set_address(struct sockaddr_in address){
	this->_address = address;
}

int Socket::socket_fd(){
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	if (serverSocket == -1) {
		std::cerr << "Failed to create socket" << std::endl;
		return EXIT_FAILURE;
	}
	this->_socket_server_fd = serverSocket;
	// fcntl(this->_socket_server_fd, F_SETFL, O_NONBLOCK); // set socket to non-blocking
	return EXIT_SUCCESS;
}

int Socket::address_socket(){
	this->_address.sin_family = AF_INET;
	// this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_addr.s_addr = inet_addr(this->_host.c_str());// need to check host assignment!!!
	this->_address.sin_port = htons(this->_port);
	memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));
	return EXIT_SUCCESS;
}

int Socket::bind_socket(){
	if (bind(this->_socket_server_fd, (struct sockaddr*)&this->_address, sizeof(this->_address)) < 0) {
		std::cerr << "Failed to bind socket to address" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Socket::listen_socket(){
	if (listen(this->_socket_server_fd, SOMAXCONN) < 0) {
		std::cerr << "Failed to listen for connections" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Socket::start_server(){
	if (socket_fd() == EXIT_FAILURE)
		return EXIT_FAILURE;
	std::cout << "Socket created" << std::endl;
	if (address_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	std::cout << "Address assigned" << std::endl;
	if (bind_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	std::cout << "Socket bound" << std::endl;
	if (listen_socket() == EXIT_FAILURE)
		return EXIT_FAILURE;
	std::cout << "Socket listening" << std::endl;
	return EXIT_SUCCESS;
}

int Socket::accept_connection() {
    sockaddr_in address_client;
    socklen_t addrlen_client = sizeof(address_client);

    int _socket_client_fd = accept(this->_socket_server_fd, (struct sockaddr*)&address_client,	&addrlen_client);
    if (_socket_client_fd < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
		return EXIT_FAILURE;
    }
    this->_socket_client_fd = _socket_client_fd;
    return EXIT_SUCCESS;
}

int Socket::read_socket(){
	int valread = read(this->_socket_client_fd, this->_buffer, BUFFER_SIZE);
	if (valread < 0) {
		std::cerr << "Failed to read from socket" << std::endl;
		return EXIT_FAILURE;
	}
	return valread;
}

// int Socket::write_socket(std::string str){
// 	int valwrite = write(this->_socket_client_fd, str.c_str(), str.length());
// 	if (valwrite < 0) {
// 		std::cerr << "Failed to write to socket" << std::endl;
// 		return EXIT_FAILURE;
// 	}
// 	return valwrite;
// }

int Socket::send_response(std::string str){
	int valwrite = send(this->_socket_client_fd, str.c_str(), str.length(), 0);
	if (valwrite < 0) {
		std::cerr << "Failed to write to socket" << std::endl;
		return EXIT_FAILURE;
	}
	return valwrite;
}


int Socket::close_socket_client(){
	close(this->_socket_client_fd);
	return EXIT_SUCCESS;
}

int Socket::close_socket_server(){
	close(this->_socket_server_fd);
	return EXIT_SUCCESS;
}


int Socket::poll_socket(){
	struct pollfd fds[1];
	fds[0].fd = this->_socket_server_fd;
	fds[0].events = POLLIN;
	int ret = poll(fds, 1, 1000); 
	if (ret < 0)
	{
		std::cerr << "Poll error" << std::endl;
		return EXIT_FAILURE;
	}
	if (ret == 0)
	{
		std::cerr << "Poll timeout" << std::endl;
		return EXIT_FAILURE;
	}
	if (fds[0].revents & POLLIN)
	{
		std::cout << "Data is available now" << std::endl;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int Socket::poll_loop()
{
	while (1)
	{
		if (poll_socket() == EXIT_SUCCESS)
			break;
	}
	return EXIT_SUCCESS;
}

