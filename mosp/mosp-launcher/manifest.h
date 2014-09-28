#ifndef _H_MANIFEST
#define _H_MANIFEST

#include <hash_map>
#include <string>

class Manifest
{
public:
	Manifest(int version, std::hash_map<std::string, std::string> fileList) :
		version(version),
		fileList(fileList)
	{}

	~Manifest() {};

private:
	int version;
	std::hash_map<std::string, std::string> fileList; //<Hash, FilePath>
};

#endif