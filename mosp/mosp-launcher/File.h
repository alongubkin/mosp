#ifndef _H_FILE
#define _H_FILE

class File
{
public:
	File(unsigned char* fileContents, unsigned int fileLength) :
		fileContents(fileContents),
		fileLength(fileLength)
	{};

	~File() { delete fileContents; };

private:
	unsigned char* fileContents;
	unsigned int fileLength;
};

#endif