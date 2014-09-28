#include <iostream>
#include "downloader.h"

#define HTTP_SERVER_URL "http://127.0.0.1:8080/"

int main()
{
	Downloader downloader(HTTP_SERVER_URL);
	std::vector<unsigned char> v = downloader.DownloadFile("CanBusDriver.c");

	for (int i = 0; i < v.size(); i++)
		std::cout << v[i];

	std::cout << std::endl;

	getchar();

	return 0;
}

