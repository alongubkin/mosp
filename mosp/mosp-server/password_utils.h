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

	std::string HashPassword(std::string password, std::string salt)
	{
		std::vector<unsigned char> vec;
		HexToBytes(salt, vec);

		unsigned char* out = new unsigned char[32];
		PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.length(), &vec[0], vec.size(), 20000, 32, out);
		
		std::string result;
		BytesToHex(out, 32, result);

		delete[] out;
		return result;
	}

	std::string GenerateSalt()
	{
		unsigned char* salt = new unsigned char[32];
		RAND_bytes(salt, 32);

		std::string result;
		BytesToHex(salt, 32, result);

		delete[] salt;
		return result;
	}

	void BytesToHex(const unsigned char* data, size_t length,
		std::string& str)
	{
		// Clear output
		str.clear();

		// No data? Then we're done
		if (0 == length)
			return;

		// Output is twice the length of input length
		str.resize(length * 2, ' ');

		// Working with 4-bit nybbles, we can use the value as
		// index to character
		static const std::string hex_char = "0123456789abcdef";

		for (size_t i = 0; i < length; ++i)
		{
			// High nybble
			str[i << 1] = hex_char[(data[i] >> 4) & 0x0f];
			// Low nybble
			str[(i << 1) + 1] = hex_char[data[i] & 0x0f];
		}
	}

	void HexToBytes(const std::string& str,
		std::vector<unsigned char>& data)
	{
		// Clear output
		data.clear();

		// No data? Then we're done
		if (str.empty())
			return;

		// Must be prepared that string can have odd number of
		// nybbles, in which case the first is treated like the low
		// nybble of the first byte
		size_t lengthOverflow = str.length() % 2;

		// This also affects the length of the data buffer we
		// allocate (need full  byte for nybble)
		const size_t length = lengthOverflow + str.length() / 2;
		data.resize(length);

		// Buffer for byte conversion
		static char buf[3];
		buf[2] = 0;
		// End of input
		char* pend = &buf[2];

		// Iterators for input and output
		size_t i = 0;
		size_t c = 0;

		// If the first nybble is a low, we'll do it separately
		if (1 == lengthOverflow)
		{
			buf[0] = '0';
			buf[1] = str[c++];
			unsigned char x = static_cast<unsigned char>
				(strtoul(buf, &pend, 16));

			// Parsing should stop at terminating zero
			if (pend != &buf[2])
			{
				std::string e = "Invalid character in hex string: \'";
				e += *(pend);
				e += "'";
				throw std::invalid_argument(e);
			}
			data[i++] = x;
		}

		// For each output byte, we use two input characters for
		// high and low nybble, respectively
		for (; i < length; ++i)
		{
			buf[0] = str[c++];
			// strtoul accepts initial whitespace or sign, we can't
			if (!isxdigit(buf[0]))
			{
				std::string e = "Invalid character in hex string: \'";
				e += buf[0];
				e += "'";
				throw std::invalid_argument(e);
			}

			buf[1] = str[c++];
			unsigned char x = static_cast<unsigned char>
				(strtoul(buf, &pend, 16));

			// Parsing should stop at terminating zero
			if (pend != &buf[2])
			{
				std::string e = "Invalid character in hex string: \'";
				e += *(pend);
				e += "'";
				throw std::invalid_argument(e);
			}

			data[i] = x;
		}
	}
}

#endif