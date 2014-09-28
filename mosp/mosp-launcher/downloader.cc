#include "downloader.h"
#include <thread>
#include <iostream>

Downloader::Downloader(const std::string& host)
{
	this->host = host;
	curlHandle = curl_easy_init();
}

Downloader::~Downloader()
{
	curl_easy_cleanup(curlHandle);
}

std::vector<unsigned char> Downloader::DownloadFile(const std::string& filePath)
{
	std::string combinedPath(host);
	combinedPath.append(filePath);
	std::vector<unsigned char> buffer;

	curl_easy_reset(curlHandle); // Maybe not neccesary?
	curl_easy_setopt(curlHandle, CURLOPT_URL, combinedPath.c_str());
	CURLcode res = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, Downloader::WriteData);

	std::cout << "Downloading \"" << filePath << "\"... ";
	CURLcode cc = curl_easy_perform(curlHandle);

	// Blocks until it receives data (DIRTY HACK)
	// TODO: Find a better to download using libcurl in a blocking mode
	while (buffer.size() == 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(20));

	std::cout << "OK" << std::endl;

	return buffer;
}

size_t Downloader::WriteData(void* buffer, size_t size, size_t nmemb, void* userdata)
{
	int realsize = size * nmemb;

	for (int i = 0; i < realsize; i++)
		((std::vector<unsigned char>*)userdata)->push_back(((unsigned char*)buffer)[i]);
	
	return realsize;
}

