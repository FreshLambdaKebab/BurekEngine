#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "TextureCache.h"

//static class to manager resources
class ResourceManager
{
public:

	static const Texture& GetTexture(const std::string& texturePath);
	
private:
	static TextureCache m_textureCache;

};

#endif //_RESOURCE_MANAGER_H
