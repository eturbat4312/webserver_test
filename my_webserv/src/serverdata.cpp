#include "../includes/config.hpp"

void	Servers::enterPorts(std::vector<std::string> info){
	for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++){
		int port = atoi((*it).c_str()); // port : 0 ????????????????
		if (port < 0 || port > 65535)
			throw std::invalid_argument("Invalid port number!");
		else{
			if (std::find(this->port.begin(), this->port.end(), port) != this->port.end())
				throw std::invalid_argument("Duplicate port numbers!");
			this->port.push_back(port);
		}
	}
}

void	Servers::enterBodySize(std::vector<std::string> info){
	if (info.size() != 3)
	{
		std::string	sizeBody = info[1];
		char unit = tolower(sizeBody[sizeBody.size() - 1]);
		if (unit == 'm')
		{
			trim(sizeBody, 'm');
			client_body_size = ft_stoi(sizeBody);
			client_body_size = client_body_size * 1024;
		}
		else
			throw std::invalid_argument("Invalid max body size");
	}
	else
		throw std::invalid_argument("Syntax error: Body size, wrong number of arguments");
}

void	Servers::enterData(std::vector<std::string> info){
	trim(info[info.size() - 1], ';');
	if (info[info.size() - 1].empty())
		info.erase(info.end() - 1);
	//std::cout << "info0: " << info[0] << std::endl;
	if (info.size() > 1 && info[0] == "listen"){
		enterPorts(info);
	}
	else if (info.size() >= 2 && info[0] == "server_name"){
		for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++){
			if (find(this->server_name.begin(), this->server_name.end(), *it) == this->server_name.end())
				this->server_name.push_back(*it);
		}
		// for (std::vector<std::string>::iterator it = server_name.begin(); it != server_name.end(); it++)
		// 	std::cout << "server name : " << *it << std::endl;
		// for (std::vector<int>::iterator it = port.begin(); it != port.end(); it++)
		// 	std::cout << "this port: " << *it << std::endl;
	}
	else if (info.size() > 1 && info[0] == "error_page")
	{

		if (info.size() == 3 || info.size() == 2)
			errorPage(info);
		else
			throw std::invalid_argument("Wrong number of arguments");
	}
	else if (info.size() > 1 && info[0] == "client_max_body_size")
	{
		//std::cout << "here " << std::endl;
		enterBodySize(info);
	}
	else if (info.size() > 1 && info[0] == "host"){
		if (!this->host.empty())
			throw std::invalid_argument("Syntax Error: Duplicate host");
		//std::cout << "info.size: " << info.size() << std::endl;
		if (info.size() == 2)
			checkHost(info[1]);
	}
	else if (info.size() > 1 && info[0] == "root")
	{
		if (info.size() == 2)
			this->root = info[1];
		else
			throw std::invalid_argument("Syntax Error: wrong number of arguments");
	}
	else if (info.size() > 1 && info[0] == "index"){
		if(info.size() == 2)
		{
			if (!this->index.empty())
				throw std::invalid_argument("Syntax Error: Invalid index");
			this->index = info[1];
		}
	}
	else
		if(info.size() > 0 && !info[0].empty())
			throw std::invalid_argument("Syntax error: Unknown argument");

	
}