#include "file_manager.h"
#include <hash_map>
#include <fstream>
#include "tinydir.h"
#include "md5_manager.h"

std::vector<std::string> FileManager::GetFileList()
{
	std::vector<std::string> fileList;

	tinydir_dir dir;
	tinydir_open(&dir, "./");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		printf("%s", file.name);

		if (file.is_dir)
		{
			printf("/");
		}

		printf("\n");
		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	return fileList;
}

Manifest FileManager::GenerateLocalManifest()
{
	int version;
	std::hash_map<std::string, std::string> fileList;

	tinydir_dir dir;
	tinydir_open(&dir, "./");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (file.is_reg)
		{
			unsigned char* fileContents = LoadFile(file.name);
			MD5Manager::GetMD5String(fileContents, )
		}
		else if (file.is_dir)
		{
			printf("/");
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	return Manifest(version, fileList);
}

File FileManager::LoadFile(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	unsigned char* buffer = new unsigned char[length];
	file.read((char*)buffer, length);
	file.close();

	return File(buffer, length);
}