#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H


#include <map>

#include "../../include/SDL_opengl.h"

#include "../event/reshape/ReshapeListener.h"
#include "../event/reshape/ReshapeEvent.h"
#include "../core/Controller.h"
#include "Texture.h"

using namespace std;

namespace XOR {

/**
 * A factory that takes in one of several image types and returns a texture'
 * that can be used by a Paint object
 */
class TextureFactory : public ReshapeListener
{
	
public:

	/** 
	 * Returns an instance of the texture factory
	 */
	static TextureFactory * GetInstance();


	/**
	 * A method for creating textures. Employs singleton texture creation
	 */
	Texture * createTexture(const char * pathToFile);

	Texture * createTextureFromMem(char * data, int size, const char * name);


    /**
     * Because the reshape results in a new rendering context, the textures
     * must be regenerated. this routine updates all textures stored by the
     * factory. If you create textures outside the factory, you may want to add
     * a them to the factory's collection just to take advantage of this timely
     * regeneration.
     *
     * @param event    The ReshapeEvent describing the new window position. This
     * value is totally ignored, all we need to know is that the display
     * context has been recreated, and our texture data is hosed.
     */
    void handleReshape(ReshapeEvent * event);


	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-XOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Texture * CreateTexture(String pathToFile);


private:

	/**
	 * Default Constructor
	 * Sets up texture parameters. Should these be changeable, or at least exposed
     * to the constructor?
	 */
	TextureFactory();

    void initializeTextureSettings();

	//container for textures
	map<const char *, Texture *> textures;

	static TextureFactory * _textureFactory;

};

}

#endif			// TEXTUREFACTORY_H

