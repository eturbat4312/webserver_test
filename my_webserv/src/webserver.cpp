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

