#include "md5_manager.h"

std::string MD5Manager::DigestToString(const unsigned char* digest)
{
	char mdString[33];

	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
		sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

	return std::string(mdString);
}

std::string MD5Manager::GetMD5String(const unsigned char* buffer, int size)
{
	unsigned char digest[MD5_DIGEST_LENGTH];
	MD5((unsigned char*)buffer, size, digest);
	return DigestToString(digest);
}