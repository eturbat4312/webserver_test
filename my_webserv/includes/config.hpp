#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <exception>
#include <algorithm>
#include <sstream>
#include "fcntl.h"

#include "webserver.hpp"

class Locations;

class	errorPages{
	public:
		int	status_code;
		std::string path;
		std::string page;
};

class Servers{
public:
	std::vector<std::string> raw_server;
	std::string index;
	std::vector<std::string> server_name;
	std::vector<int> port;
	std::string root;
	std::string returned;
	bool	isDuplicate;
	int	_port;
	int	socket_fd;
	long	client_body_size;
	struct sockaddr_in _address;
	std::string host;

	std::vector<Locations> locations;
	std::vector<errorPages> error_page;


	void	split_locations(std::vector<std::string> &server_info);
	void	checkSyntaxError(std::vector<std::string>& server_info);
	void	enterData(std::vector<std::string> info);
	void	enterPorts(std::vector<std::string> info);
	void	errorPage(std::vector<std::string> info);
	void	enterBodySize(std::vector<std::string> info);
	void	checkHost(std::string info);
};

class	Config{
public:
	std::vector<Servers> servers;
	void	parse(std::string filename);
	void	parse_servers(Servers& server);
};

class Locations{
public:
	std::vector<std::string> raw_location;
	std::string root;
	std::string directive;
	std::string returned;
	std::string upload_enable;
	std::string	upload_store;


};

std::vector<std::string> split(const std::string& str, char delimiter);
std::string trim(std::string &s, char c);
int	allcodes(int code);
int	ft_stoi(std::string str);
