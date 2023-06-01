#include "../includes/config.hpp"

void	Servers::split_locations(std::vector<std::string>& server_info){
	for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++){
		Locations location;
		int bracket = 0;
		std::vector<std::string> info = split(*it, ' ');
		// std::cout << "info : " << info[0] << std::endl;
		if (info[0] == "location")
		{
			if (info.size() != 3 || (info[1][0] != '/' && info[1] != "*.php" && info[1] != "*.py") || info[2] != "{")
				throw std::invalid_argument("Conf file location error");
			bracket++;
			std::vector<std::string> raw_location;
			raw_location.push_back(info[1]);
			// std::cout << "raw_location size: " << raw_location.size() << std::endl;
			it = server_info.erase(it);
			//std::cout << *it << std::endl;
			while (it != server_info.end() && (*it)[0] != '}')
			{
				if (!((*it).empty()))
					raw_location.push_back(*it);
				it = server_info.erase(it);
			}
			// for (std::vector<std::string>::iterator ite = raw_location.begin(); ite != raw_location.end(); ite++)
			// {
			// 	std::cout << *ite << std::endl;
			// }
			location.raw_location = raw_location;
			locations.push_back(location);
		}
		if ((*it)[0] == '}')
			*it = "";
	}
}