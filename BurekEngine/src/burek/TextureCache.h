#ifndef _TEXTURE_CACHE_H
#define _TEXTURE_CACHE_H

#include <map>

#include "Texture.h"
#include <string>

namespace burek
{

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		const Texture& GetTexture(const std::string& filePath);

	private:
		std::map<std::string, Texture> m_textureMap;
	};

}

#endif //_TEXTURE_CACHE
