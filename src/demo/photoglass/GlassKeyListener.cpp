#include "GlassKeyListener.h"

using namespace XOR;
/**
 * In order for this keyboard controller class to work we have to pass in an
 * instance of the controller and the PhotoAlbum
 */
GlassKeyListener::GlassKeyListener(PhotoGlass * photoglass)
{
	//	_ctrl = ctrl;
	_photoglass = photoglass;
}


void GlassKeyListener::handleKey_F5()
{
}

/* 
void GlassKeyListener::handleKey_a()
{
	//_ctrl->getCamera()->incrementRotation(0, -10.0f);
}

void GlassKeyListener::handleKey_d()
{
	//_ctrl->getCamera()->incrementRotation(0, 10.0f);
}

void GlassKeyListener::handleKey_w()
{
	//_ctrl->getCamera()->walk(0.15f, new TimedInterpolation(200,NULL));
}

void GlassKeyListener::handleKey_s()
{
	//_ctrl->getCamera()->walk(-0.15f, new TimedInterpolation(200,NULL));
}

void GlassKeyListener::handleKey_q()
{
	//_ctrl->getCamera()->incrementRotation(2, 5.0f);
}

void GlassKeyListener::handleKey_e()
{
	//_ctrl->getCamera()->incrementRotation(2, -5.0f);
}

void GlassKeyListener::handleKey_c()
{
	//_ctrl->getCamera()->incrementRotation(1, 5.0f);
}

void GlassKeyListener::handleKey_z()
{
	//_ctrl->getCamera()->incrementRotation(1, -5.0f);
}
*/
/**
 * Left, right, up handling functions
 */
void GlassKeyListener::handleKey_Down()
{
	_photoglass->changeSelection(1);
}

void GlassKeyListener::handleKey_Up()
{
	_photoglass->changeSelection(2);
}
void GlassKeyListener::handleKey_Left()
{
	_photoglass->changeSelection(4);
}

void GlassKeyListener::handleKey_Right()
{
	_photoglass->changeSelection(3);
}

/**
 * VI STYLE left, right, up, and down
 */
void GlassKeyListener::handleKey_k()
{
	handleKey_Up();
}

void GlassKeyListener::handleKey_h()
{
	handleKey_Left();
}
void GlassKeyListener::handleKey_j()
{
	handleKey_Down();
}

void GlassKeyListener::handleKey_l()
{
	handleKey_Right();
}

/*
 * Spacebar will bring a picture to the front
 */
void GlassKeyListener::handleKey_Space()
{
}

