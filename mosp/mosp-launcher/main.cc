#include <iostream>
#include <ostream>
#include <curl/curl.h>

using namespace std;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

int main()
{
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/");
	size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	CURLcode cc =  curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	getchar();

	return 0;
}

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	cout << (char*)buffer << endl;

	return 1;
}