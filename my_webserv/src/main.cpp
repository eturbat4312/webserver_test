#include "../includes/config.hpp"
#include "../includes/webserver.hpp"
#include "../includes/socket.hpp"

int	main(int argc, char *argv[])
{
	if (argc >= 2)
	{
		// std::cerr << "\nError❗\n" <<"Too many arguments\n" << std::endl;
		// return EXIT_FAILURE;

		//MYTEST
		Servers server_test;
		server_test.simple_server();

		std::vector<Servers> servers;
		servers.push_back(server_test);

		webServer webserver(servers);

		// socket socket();
		Socket socket(8080, "127.0.0.1");
		
		if (socket.start_server() == EXIT_FAILURE)
			return EXIT_FAILURE;

		while (true)
		{
			socket.poll_loop();

			std::cout << "Accepting connection" << std::endl;
			socket.accept_connection();

			std::cout << "Reading from socket" << std::endl;
			
			if (socket.read_socket() != EXIT_FAILURE)
			{
				std::string request = socket.get_buffer();

				// Check the type of request
				if (request.substr(0, 3) == "GET")
				{
					// Extract the path from the request
					std::string path = request.substr(4, request.find(" ", 4) - 4);

					std::cout << "Processing GET request for path: " << path << std::endl;

					// Handle the GET request based on the path
					if (path == "/")
					{
						std::ifstream file("default.html");
						std::stringstream buffer;
						buffer << file.rdbuf();
						std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + buffer.str();
						socket.send_response(response);
					}
					else
					{
						// Handle other paths or return a 404 error
						std::string response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found";
						socket.send_response(response);
					}
				}
				else if (request.substr(0, 3) == "ADD")
				{
					// Extract the data to be added from the request
					std::string data = request.substr(4);

					std::cout << "Processing ADD request with data: " << data << std::endl;

					// Implement the logic to add the data

					std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData added successfully";
					socket.send_response(response);
				}
				else if (request.substr(0, 6) == "DELETE")
				{
					// Extract the data to be deleted from the request
					std::string data = request.substr(7);

					std::cout << "Processing DELETE request with data: " << data << std::endl;

					// Implement the logic to delete the data

					std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData deleted successfully";
					socket.send_response(response);
				}
				else
				{
					// Invalid request
					std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request";
					socket.send_response(response);
				}
			}
			std::cout << "Sending response" << std::endl;
			std::ifstream file("default.html");
			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + buffer.str();
			socket.send_response(response);

			std::cout << "Closing socket" << std::endl;
			socket.close_socket_client();
		}
		std::cout << "Closing server" << std::endl;
		socket.close_socket_server();

		return 0;
	}

	//int port = 8080;
	std::cout << "here is it\n";
	std::string localhost = "127.0.0.1";
	
	Config config;
	if (argc == 1)
		config.parse("conf/default.conf");
	else
		config.parse(argv[1]);

	std::cout << "here is ittt\n";
	
	return 0;
}