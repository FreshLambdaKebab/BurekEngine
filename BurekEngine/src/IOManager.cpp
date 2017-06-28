#include "IOManager.h"

#include <fstream>

bool IOManager::ReadFileToBuffer(std::vector<unsigned char>& buffer, const std::string & filePath)
{
	std::ifstream file(filePath,std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	//seek to end of file
	file.seekg(0, std::ios::end);

	//get file size
	int fileSize = file.tellg();
	file.seekg(0,std::ios::beg);

	//reduce file size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&buffer[0],fileSize);

	return true;
}
