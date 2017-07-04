#include "ImageLoader.h"

#include "picoPNG.h"
#include "IOManager.h"
#include "Debug.h"

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

Texture ImageLoader::LoadPNG(const std::string & path)
{
	Texture texture = {};

	std::vector<unsigned char>in;
	std::vector<unsigned char>out;
	unsigned long width, height;

	if (IOManager::ReadFileToBuffer(in, path) == false)
		FatalError("failed to load .PNG file to buffer");

	int error = decodePNG(out,width,height,&in[0],in.size());
	if (error != 0)
	{
		FatalError("decodePNG failed with error: " + std::to_string(error));
	}

	glGenTextures(1, &texture.ID);

	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//set texture dims
	texture.width = width;
	texture.height = height;

	return texture;
}
