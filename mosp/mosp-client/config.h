#ifndef _H_CONFIG
#define _H_CONFIG

#include <hash_map>
#include <string>
#include <vector>
#include <assert.h>

class Config
{
public:
	static void Load();
	static std::string GetProperty(const std::string& name) { return properties[name]; }

private:
	static std::hash_map<std::string, std::string> properties;

	static std::vector<std::string> Split(const std::string& s, char seperator);
};

#endif