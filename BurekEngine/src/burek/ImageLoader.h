#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include "Texture.h"
#include <string>

namespace burek
{

	class ImageLoader
	{
	public:
		ImageLoader();
		~ImageLoader();

		static Texture LoadPNG(const std::string& path);

	private:

	};

}

#endif
