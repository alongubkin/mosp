#ifndef _H_DOWNLOADER
#define _H_DOWNLOADER

#include <string>
#include <vector>
#include <curl/curl.h>


class Downloader
{
public:
	Downloader(const std::string& host);
	~Downloader();

	std::vector<unsigned char> DownloadFile(const std::string& filePath);

private:
	std::string host;
	CURL* curlHandle;
	
	static size_t WriteData(void* buffer, size_t size, size_t nmemb, void* userdata);
};

#endif