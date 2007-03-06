#include "PhotoKeyboardListener.h"

/**
 * In order for this keyboard controller class to work we have to pass in an
 * instance of the controller and the PhotoAlbum
 */
PhotoKeyboardListener::PhotoKeyboardListener(Controller * ctrl, PhotoAlbum * photoalbum)
{
	_ctrl = ctrl;
	_photoalbum = photoalbum;
}

void PhotoKeyboardListener::handleKey_R()
{
	_ctrl->getViewer()->clear();
}


void PhotoKeyboardListener::handleKey_S()
{
	_ctrl->getViewer()->incrementTranslation(new Vector3D(0,0,1), new TimedInterpolation(1000, _photoalbum));
}

void PhotoKeyboardListener::handleKey_A()
{
	_ctrl->getViewer()->incrementTranslation(
		new Vector3D(0,0,-1), new TimedInterpolation(1000, _photoalbum));
}
	
/** 
 * When you hit the 0 key, all the pictures are set back to 
 * the grid configuration
 *
 * legacy code
 */
/*void PhotoKeyboardListener::handleKey_0()
{
	vector<Object3D*>::iterator iter = pics.begin();
        vector<Object3D*>::iterator end  = pics.end();

    int i=0;
    while (iter != end )
    {
    	++i;
        if (i == 9)
		{
        	(*iter)->incrementScalar(new Vector3D(1, 0, 0), new TimedInterpolation(1000, this));
            //(*iter)->setTranslation(new Dimension3D(0, 0, 0), new TimedInterpolation(1000, this));
        }
        ++iter; 
    }
}*/

/**
 * handleKey_3() performs the Magnotti transform
 */
void PhotoKeyboardListener::handleKey_3()
{
	_photoalbum->magnottiTransform();
}

void PhotoKeyboardListener::handleKey_F5()
{
	_photoalbum->resetAllPhotos();
}
/* // does this work?
void PhotoKeyboardListener::handleKey_p()
{
	_ctrl->getViewer()->printDebugInfo();
}*/

void PhotoKeyboardListener::handleKey_a()
{
	_ctrl->getViewer()->incrementRotation(0, -10.0f);
}

void PhotoKeyboardListener::handleKey_d()
{
	_ctrl->getViewer()->incrementRotation(0, 10.0f);
}

void PhotoKeyboardListener::handleKey_w()
{
	_ctrl->getViewer()->walk(0.15f, new TimedInterpolation(200,NULL));
}

void PhotoKeyboardListener::handleKey_s()
{
	_ctrl->getViewer()->walk(-0.15f, new TimedInterpolation(200,NULL));
}

void PhotoKeyboardListener::handleKey_q()
{
	_ctrl->getViewer()->incrementRotation(2, 5.0f);
}

void PhotoKeyboardListener::handleKey_e()
{
	_ctrl->getViewer()->incrementRotation(2, -5.0f);
}

void PhotoKeyboardListener::handleKey_c()
{
	_ctrl->getViewer()->incrementRotation(1, 5.0f);
}

void PhotoKeyboardListener::handleKey_z()
{
	_ctrl->getViewer()->incrementRotation(1, -5.0f);
}

/**
 * Left, right, up handling functions
 */
void PhotoKeyboardListener::handleKey_Down()
{
	_photoalbum->moveSelectedDown();
}

void PhotoKeyboardListener::handleKey_Up()
{
	_photoalbum->moveSelectedUp();
}
void PhotoKeyboardListener::handleKey_Left()
{
	_photoalbum->moveSelectedLeft();
}

void PhotoKeyboardListener::handleKey_Right()
{
	_photoalbum->moveSelectedRight();
}

/**
 * VI STYLE left, right, up, and down
 */
void PhotoKeyboardListener::handleKey_k()
{
	_photoalbum->moveSelectedUp();
}

void PhotoKeyboardListener::handleKey_h()
{
	_photoalbum->moveSelectedLeft();
}
void PhotoKeyboardListener::handleKey_j()
{
	_photoalbum->moveSelectedDown();
}

void PhotoKeyboardListener::handleKey_l()
{
	_photoalbum->moveSelectedRight();
}

/*
 * Spacebar will bring a picture to the front
 */
void PhotoKeyboardListener::handleKey_Space()
{
	_photoalbum->toggleViewMode();
}

void PhotoKeyboardListener::handleKeyEvent()
{
}
