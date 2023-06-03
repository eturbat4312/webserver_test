#include "../includes/config.hpp"

void	checkSemicolone(std::vector<std::string>& info){
	int	semi = 0;
	//std::cout << "checksemi" << std::endl;
	if (info[info.size() - 1][info[info.size() - 1].size() -1] == ';')
	{
		for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++){
			std::string word = *it;
			for (size_t i = 0; i < word.length(); i++)
				if (word[i] == ';')
					semi++;
		}
	}
	else
		if (!info[0].empty())
			throw std::invalid_argument("Syntax error: Semiclone missing");
		if (semi > 1)
			throw std::invalid_argument("Syntax error: Extra semicolone");
}

int	allcodes(int code){
	std::vector<int> codes;

	for (int i = 400; i < 499; i++)
		codes.push_back(i);
	for (int i = 500; i < 528; i++)
		codes.push_back(i);

	if (std::find(codes.begin(), codes.end(), code) != codes.end())
		return (true);
	return false;
}

std::string	to_String(int n)
{
	std::stringstream tmp;

	tmp << n;

	return tmp.str();
}

void Servers::checkHost(std::string info)
{
    if (info == "localhost")
    {
        host = "127.0.0.1";
        return;
    }

    int point = 0;
    std::string host;

    for (size_t i = 0; i < info.length(); i++)
    {
        char c = info[i];
        if (c == '.')
        {
            if (point > 3 || host.empty())
                throw std::invalid_argument("Syntax Error: invalid host");

            int number = atoi(host.c_str());
            if (number > 255 || number < 0)
                throw std::invalid_argument("Syntax Error: invalid host");

            host.clear();
            point++;
        }
        else if (isdigit(c))
        {
            host += c;
        }
        else
        {
            throw std::invalid_argument("Syntax Error: invalid host");
        }
    }

    if (point != 3 || host.empty())
        throw std::invalid_argument("Syntax Error: invalid host");

    int number = atoi(host.c_str());
    if (number > 255 || number < 0)
        throw std::invalid_argument("Syntax Error: invalid host");

    this->host = info;
}



std::string setErrorPage(std::string path, std::string status_code){
	std::ifstream file;
	file.open(path.c_str());

	std::string line;
	std::string lines;

	while (getline(file, line))
		lines.append(line + "\n");
	//std::cout << "lines: " << lines << std::endl;
	// continue "./srcs/Conf/error/error.html" ?????





	(void)status_code;
	return lines;
}

void	Servers::errorPage(std::vector<std::string> info){
	std::vector<int> saved_codes;

	int status = atoi(info[1].c_str());

	if (allcodes(status))
	{

		saved_codes.push_back(status);
		errorPages current;
		std::ifstream file;
		current.status_code = status;
		//std::cout << "Status code: " << current.status_code << std::endl;
		if (info.size() == 3){
			file.open(info[2].c_str());
			current.path = info[2];
			//std::cout << "Current Path: " << current.path << std::endl;
			current.page = setErrorPage(current.path, to_String(status)); // setErrorPage needs to develop and finish !!!!!!
			current.path = "./src/error/error.html";
			current.page = setErrorPage(current.path, to_String(status));
		}
		else{
			current.path = "./src/error/error.html";
			current.page = setErrorPage(current.path, to_String(status));
		}
		this->error_page.push_back(current);

	}
	else
		throw std::invalid_argument("Invalid status code !");
}

void	Servers::checkSyntaxError(std::vector<std::string>& server_info){
	server_info.erase(server_info.begin());

	for (std::vector<std::string>::iterator it = server_info.begin(); it != server_info.end(); it++){
		std::vector<std::string> info = split(*it, ' ');
		checkSemicolone(info);
		enterData(info);
	}

}