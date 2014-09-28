#include "file_manager.h"
#include <hash_map>
#include "tinydir.h"

std::vector<std::string> GetFileList()
{
	std::vector<std::string> fileList;

	tinydir_dir dir;
	tinydir_open(&dir, "/path/to/dir");

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
	return Manifest(version, fileList);
}