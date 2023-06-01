#include "../includes/config.hpp"
#include "../includes/webserver.hpp"

int	main(int argc, char *argv[])
{

	//int port = 8080;

	std::string localhost = "127.0.0.1";

	
	Config config;
	if (argc == 1)
		config.parse("../conf/default.conf");
	else{
		config.parse(argv[1]);
	}
	std::cout << "here is ittt\n";
	webServer server(config.servers);
	return 0;
}