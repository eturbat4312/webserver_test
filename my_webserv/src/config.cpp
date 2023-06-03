#include "../includes/config.hpp"

std::string trim(std::string &s, char c)
{
	std::string  str;
	size_t index = s.find_first_not_of(c);
    if (index != std::string::npos)
        str += s.substr(index);
    index = str.find_last_not_of(c);
    if (index != std::string::npos)
	{
        str = str.substr(0, index + 1);
	}
	s = str;
	return (s);
}

int	ft_stoi(std::string str)
{
	size_t	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (i != str.length())
		return (-1);
	return (res * sign);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> substrings;
    std::string current_substring;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        char c = *it;
        if (c == delimiter) {
            substrings.push_back(current_substring);
            current_substring.clear();
        } else {
            current_substring += c;
        }
    }
    if (!current_substring.empty()) {
        substrings.push_back(current_substring);
    }
    return substrings;
}


void parse_bracket(std::vector<std::string>& vector_line)
{
		int bracket_no = 0;
    std::vector<std::string>::iterator it = vector_line.begin();
    while (it != vector_line.end())
    {
        // Trim leading and trailing whitespace from the string
        std::string& str = *it;
        size_t first_non_space = str.find_first_not_of(" \t\r\n");
        size_t last_non_space = str.find_last_not_of(" \t\r\n");
        if (first_non_space == std::string::npos) {
            // The string is all whitespace, so erase it
            it = vector_line.erase(it);
        }
        else {
            // Extract the trimmed string and replace the original string
            str = str.substr(first_non_space, last_non_space - first_non_space + 1);
            if (str.size() > 0 && str[0] == '#') {
                // The trimmed string starts with '#', so erase it
                it = vector_line.erase(it);
            }
            else {
                // Move to the next element in the vector
                ++it;
            }
        }
    }
		for (std::vector<std::string>::iterator it = vector_line.begin(); it != vector_line.end(); it++)
		{
			std::vector<std::string> line = split(*it, ' ');
			if (line[0] == "server"){
				if (line.size() > 2 && line[1] != "{")
					throw std::invalid_argument("Conf file syntax error!");
				bracket_no++;
			}
			else{
				for (std::vector<std::string>::iterator it_new = line.begin(); it_new != line.end(); it_new++)
				{
					if (*it_new == "{")
					{
						if (*(it_new - 2) == "location")
							bracket_no++;
					}
					else if (*it_new == "}")
						bracket_no--;
				}
			}
		}
		if (bracket_no != 0)
			throw std::invalid_argument("Configure file syntax error! Brackets");
	
}

void split_servers(std::vector<std::string>& lines, std::vector<Servers>& servers)
{
    int braket = 0;
    std::vector<std::string> raw;
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        std::vector<std::string> line = split(*it, ' ');
        if (it == lines.begin())
            braket++;
        else
        {
            for (std::vector<std::string>::iterator iter = line.begin(); iter != line.end(); iter++)
            {
                if (*iter == "{")
                    braket++;
                else if (*iter == "}")
                    braket--;
            }
        }
        raw.push_back(*it);
        if (braket == 0)
        {
            Servers server;
            server.raw_server = raw;
            server.isDuplicate = 0;
            servers.push_back(server);
            raw.clear();
        }
    }
}

void	Config::parse_servers(Servers& server){

	server.split_locations(server.raw_server);

	server.client_body_size = -1;

	server.checkSyntaxError(server.raw_server);
}

void	Config::parse(std::string filename){
	std::ifstream fd;
	fd.open(filename.c_str());
	std::vector<std::string> vector_line;
	std::string line;
	if (!fd.is_open()){
		throw std::invalid_argument("file open failed");
	}
	while (getline(fd, line))
		if (!line.empty())
			vector_line.push_back(line.append(" \n"));
	parse_bracket(vector_line);
	
	split_servers(vector_line, servers);
	//std::cout << servers.size() << std::endl;
	if (servers.size() < 1)
		throw std::invalid_argument("No server blocks");
	std::vector<Servers>::iterator it;
	
	for (it = servers.begin(); it != servers.end(); it++)
	{
		parse_servers(*it);
	}
}