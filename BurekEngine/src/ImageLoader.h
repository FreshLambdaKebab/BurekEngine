#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include "Texture.h"
#include <string>

class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	static const Texture& LoadPNG(const std::string& path);

private:

};

#endif
