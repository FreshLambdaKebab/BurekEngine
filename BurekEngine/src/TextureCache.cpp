#include "TextureCache.h"

#include "ImageLoader.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

const Texture& TextureCache::GetTexture(const std::string& filePath) 
{
	//find texture and check if its in map
	auto mapIT = m_textureMap.find(filePath);

	//check if not in map
	if (mapIT == m_textureMap.end())
	{
		//create and load a new texture if its not there
		Texture newTex = ImageLoader::LoadPNG(filePath);

		//insert into map
		m_textureMap.insert(std::make_pair(filePath, newTex));

		return newTex;
	}

	return mapIT->second;
}
