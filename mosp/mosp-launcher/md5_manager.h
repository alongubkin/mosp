#ifndef _H_MD5Manager
#define _H_MD5Manager

#include <string>
#include <openssl/md5.h>

class MD5Manager
{
public:
	static std::string DigestToString(const unsigned char* md5);
	static std::string GetMD5String(const unsigned char* buffer, int size);

private:
	
};

#endif