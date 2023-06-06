#include "../includes/config.hpp"
#include "../includes/webserver.hpp"

int	main(int argc, char *argv[])
{
	if (argc > 2)
	{
		// std::cerr << "\nError❗\n" <<"Too many arguments\n" << std::endl;
		// return EXIT_FAILURE;

		//MYTEST
		Servers server_test;
		server_test.simple_server();

		std::vector<Servers> servers;
		servers.push_back(server_test);

		webServer webserver(servers);
		if (webserver.start_server() == EXIT_FAILURE)
			return EXIT_FAILURE;
		std::cout << "Server started" << std::endl;
		webserver.poll_loop();

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