#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include <vector>
#include <string>
#include "manifest.h"

class FileManager
{
public:
	std::vector<std::string> GetFileList();
	Manifest GenerateLocalManifest();
	
};

#endif