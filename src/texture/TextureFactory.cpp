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
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	//Done in Texture
	//glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,	GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,	GL_NEAREST);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	string str = string(pathToFile);
	Texture * temp = textures[str];

	if (temp == NULL) {
        temp = new Texture(str.c_str());

		//put the texture into the map, using the path as the key
		textures[str] = temp;
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

