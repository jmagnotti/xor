#include "TextureFactory.h"

namespace XOR {

//set the static instance to null
TextureFactory* TextureFactory::_textureFactory = 0;


/*
 * Protected Constructor
 */
TextureFactory::TextureFactory()
{
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,	GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,	GL_NEAREST_MIPMAP_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


/*
 * singleton accessor
 */
TextureFactory* TextureFactory::GetInstance()
{
	if (_textureFactory == NULL)
		_textureFactory = new TextureFactory();

	return _textureFactory;
}


/* 
 * creates and returns a texture
 */
Texture* TextureFactory::createTexture(char *pathToFile)
{
	Texture * temp = textures[pathToFile];

	if (temp == NULL)		//not in the map
	{
        temp = new Texture(pathToFile);

		//put the texture into the map, using the path as the key
		textures[pathToFile] = temp;
	}

	return temp;
}

}

