#ifndef _PASSWORD_UTILS_H
#define _PASSWORD_UTILS_H

#include <string>
#include <vector>
#include "openssl/rand.h"
#include "openssl/evp.h"

namespace mosp
{
	void BytesToHex(const unsigned char* data, size_t length, std::string& str);
	void HexToBytes(const std::string& str, std::vector<unsigned char>& data);
	std::string HashPassword(std::string password, std::string salt);
	std::string GenerateSalt();
}

#endif