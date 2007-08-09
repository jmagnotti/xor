#include "TextureFactory.h"

namespace XOR {

//set the static instance to null
TextureFactory * TextureFactory::_textureFactory = 0;


/*
 * Protected Constructor
 */
TextureFactory::TextureFactory()
{
    initializeTextureSettings();    
    Controller::GetInstance()->getWindow()->addListener(this);
}


/*
 *
 */
void TextureFactory::handleReshape(ReshapeEvent * event)
{
   initializeTextureSettings();

   map<string, Texture*>::iterator iter   = textures.begin();
   map<string, Texture*>::iterator finish = textures.end();

   while (iter != finish) {
       iter->second->regenerate();
       ++iter;
   }

}


void TextureFactory::initializeTextureSettings()
{
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,	GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/*
 * singleton accessor
 */
TextureFactory * TextureFactory::GetInstance()
{
	if (_textureFactory == NULL)
		_textureFactory = new TextureFactory();

	return _textureFactory;
}


/* 
 * creates and returns a texture
 */
Texture * TextureFactory::createTexture(const char * pathToFile)
{
	Texture * temp = textures[string(pathToFile)];

	if (temp == NULL) {
        temp = new Texture(pathToFile);

		//put the texture into the map, using the path as the key
		textures[pathToFile] = temp;
	}

	return temp;
}

/* 
 * Creates a texture from a char array of image data.
 * Useful for loading the multicast pictures.
 */
Texture * TextureFactory::createTextureFromMem(char * data, int size, const char * name)
{
	Texture * temp = textures[string(name)];

	if (temp == NULL) {
        temp = new Texture(data, size);

		//put the texture into the map, using the path as the key
		textures[string(name)] = temp;
	}

#ifdef DEBUG
	cout << "returning texture: " << name << endl;
#endif

	return temp;
}

}

