#include <iostream>
#include "downloader.h"
#include "file_manager.h"

#define HTTP_SERVER_URL "http://127.0.0.1:8080/"

int main()
{
	Downloader downloader(HTTP_SERVER_URL);
	FileManager::GetFileList();

	getchar();
	return 0;
}

