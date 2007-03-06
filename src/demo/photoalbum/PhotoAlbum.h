#ifndef PHOTOALBUM_H
#define PHOTOALBUM_H

#include "../../xor.h"
#include "xmlParser/xmlParser.h"
#include "InterpolationManager.h"
#include <string>

using namespace XOR;
using namespace std;

class PhotoAlbum : public Object3D, public InterpolationListener
{
	public:
		Controller * ctrl;
		PhotoAlbum();

		void interpolationComplete(); // unlocks keyboard
		void render();
		void draw();
		
		// The following block of functions manipulates the images
		void bringToFront(int index);
		void setCurrentPic(int index);
		void revertPic(int index);
		void magnottiTransform();
		void resetAllPhotos();
		void highlightPic();    // brings an image to front
		void unhighlightPic(int index);

		void lockKeys(int expectedInterpolations);
		void unlockKeys();	
		bool getLockState(); // not used, but probably handy
		
		// all of these functions handle "navigating" the pictures
		void moveSelectedUp();
		void moveSelectedDown();
		void moveSelectedRight();
		void moveSelectedLeft();
		void toggleViewMode(); 
	
		Dimension3D * getDimension();
		Vector3D * getBaseVector();
		void renderObject();

	private:
		void parseXML();
		int numOfPics;
		int currentPic;
		bool keyboardLocked;
		String2D * pDemo;
		vector<Object3D*> pics;
		InterpolationManager * interpolationManager;
		
		// the number of interpolations to expect before it's
		// "safe" to unlock the keys
		int expectedInterpolations;
		int receivedInterpolations;
		//int viewModeStatus; // -1 off 1 on
};



#endif
