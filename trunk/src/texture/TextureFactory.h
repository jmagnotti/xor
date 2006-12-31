#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H


#include <map>
#include <stdlib.h>
#include <string.h>

#include "../../include/SDL_opengl.h"

#include "Texture.h"
#include "TexturePPM.h"
#include "TextureBMP.h"
#include "TextureTGA.h"

using namespace std;

namespace XOR {

/**
 * A factory that takes in one of several image types and returns a texture'
 * that can be used by a Paint object
 */
class TextureFactory
{
	
public:

	/** 
	 * Returns an instance of the texture factory
	 */
	static TextureFactory * GetInstance();


	/**
	 * A method for creating textures. Employs singleton texture creation
	 */
	Texture * createTexture(char* pathToFile);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Texture * CreateTexture(String pathToFile);


protected:

	//container for textures
	map<char*, Texture*> textures;


	/**
	 * Default Constructor
	 * Sets up texture parameters. Should these be changeable, or at least exposed
     * to the constructor?
	 */
	TextureFactory();


private:

	static TextureFactory* _textureFactory;

};

}

#endif			//TEXTUREFACTORY_H
