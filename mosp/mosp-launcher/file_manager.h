#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER

#include <vector>
#include <string>
#include "manifest.h"
#include "File.h"

class FileManager
{
public:
	static std::vector<std::string> GetFileList();
	static Manifest GenerateLocalManifest();


private:
	static File LoadFile(const std::string& filePath);
};

#endif