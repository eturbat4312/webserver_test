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

			// std::cout << "Reading from socket" << std::endl;
			// socket.read_socket();

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