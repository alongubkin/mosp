#include "config.h"
#include <fstream>
#include <boost/algorithm/string.hpp>

std::hash_map<std::string, std::string> Config::properties = std::hash_map<std::string, std::string>();

void Config::Load()
{
	std::ifstream file("config.cfg", std::ios::binary);

	std::string line;
	
	do
	{
		std::getline(file, line);
		boost::erase_all(line, "\r");
		boost::erase_all(line, "\n");
		std::vector<std::string> v = Split(line, '=');
		properties[v[0]] = v[1];
	} while (!file.eof());

	file.close();
} 

std::vector<std::string> Config::Split(const std::string& s, char seperator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		prev_pos = ++pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

	return output;
}
