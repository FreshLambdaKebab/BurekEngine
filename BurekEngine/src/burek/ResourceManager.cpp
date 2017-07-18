#include "ResourceManager.h"

namespace burek
{

	TextureCache ResourceManager::m_textureCache;

	const Texture& ResourceManager::GetTexture(const std::string & texturePath)
	{
		return m_textureCache.GetTexture(texturePath);
	}

}
