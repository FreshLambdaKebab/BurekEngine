#ifndef _IO_MANAGER_H
#define _IO_MANAGER_H

#include <vector>

class IOManager
{
public:
	static bool ReadFileToBuffer(std::vector<char>& buffer,const std::string& filePath);
	
};

#endif
