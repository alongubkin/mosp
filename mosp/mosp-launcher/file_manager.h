#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include <vector>
#include <string>
#include "manifest.h"

class FileManager
{
public:
	static std::vector<std::string> GetFileList();
	static Manifest GenerateLocalManifest();
	
};

#endif