#ifndef _IO_MANAGER_H
#define _IO_MANAGER_H

#include <vector>

namespace burek
{

	class IOManager
	{
	public:
		static bool ReadFileToBuffer(std::vector<unsigned char>& buffer, const std::string& filePath);

	};

}

#endif
