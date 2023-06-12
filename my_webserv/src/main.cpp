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
		socket.start_server();

		// while (true)
		// {
		// 	if (socket.accept_connection() == EXIT_FAILURE)
		// 		continue;

		// 	std::cout << "Reading from socket" << std::endl;
		// 	socket.read_socket();

		// 	std::cout << "Writing to socket" << std::endl;
		// 	std::ifstream file("website/default.html");
		// 	std::stringstream buffer;
		// 	buffer << file.rdbuf();
		// 	std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + buffer.str();
		// 	socket.write_socket(response);

		// 	std::cout << "Sending response" << std::endl;
		// 	if (socket.send_response() == EXIT_FAILURE)
		// 		continue;
			
		// 	std::cout << "Closing socket" << std::endl;
		// 	socket.close_socket();
		// }

		while (true)
		{
			while (socket.poll_loop() == EXIT_FAILURE)
				continue;
			std::cout << "Reading from socket" << std::endl;
			socket.read_socket();
			
			std::cout << "Writing to socket" << std::endl;
			std::ifstream file("website/default.html");
			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + buffer.str();
			socket.write_socket(response);

			std::cout << "Sending response" << std::endl;
			if (socket.send_response() == EXIT_FAILURE)
				continue;

			std::cout << "Closing socket" << std::endl;
			socket.close_socket();
		}
		

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