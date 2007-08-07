#include "XavierConfiguration.h"

namespace XOR
{

XavierConfiguration::XavierConfiguration()
{
}

const char * XavierConfiguration::getWindowTitle() const
{
	return "XOR 2.0";
}

double XavierConfiguration::getFieldOfView()
{
	return 60.0;
}

double XavierConfiguration::getNearClip()
{
	return 0.01f;
}

double XavierConfiguration::getFarClip()
{
	return 1000.0f;
}

Vector2D * XavierConfiguration::getWindowPosition() const
{
	return new Vector2D(200,100);
}

Dimension2D * XavierConfiguration::getWindowSize() const
{
	return new Dimension2D(800, 500);
}

int XavierConfiguration::getColorDepth()
{
	return 32;
}

Uint32 XavierConfiguration::getVideoFlags()
{
	
#ifdef WIN32
	return SDL_OPENGL;	// SDL support for resizing on Win32 is sketchy
#else
	return SDL_OPENGL | SDL_RESIZABLE;
#endif
	
}

int XavierConfiguration::getWallMode()
{
	return Camera::WALL_MODE_NONE;
}

bool XavierConfiguration::isFullScreen()
{
	return true;
}

const float * XavierConfiguration::getBackgroundColor()
{
	return Color::DARK_NAVY;
}

CoordinateSystem * XavierConfiguration::getCoordinateSystem() const
{
	return CoordinateSystemFactory::GetDefaultCoordinateSystem();
}

EventFactory * XavierConfiguration::getEventFactory() const
{
	return InputEventProxyFactory::GetInstance();
}

Vector2D * XavierConfiguration::getWallOffset() const
{
	return new Vector2D(0.0f, 0.0f);
}

int XavierConfiguration::getGLShadeModel()
{
	return GL_SMOOTH;
}

bool XavierConfiguration::isGLBlendEnabled()
{
	return true;
}

bool XavierConfiguration::isGLDepthTestEnabled()
{
	return true;
}

bool XavierConfiguration::isGLFogEnabled()
{
	return true;
}

int XavierConfiguration::getGLFogMode()
{
	return GL_LINEAR;
}

int XavierConfiguration::getGLFogStart()
{
	return -5;
}

int XavierConfiguration::getGLFogEnd()
{
	return 30;
}

const float * XavierConfiguration::getGLFogColor()
{
	return Color::BLACK;
}

bool XavierConfiguration::isGLTextureEnabled()
{
	return true;
}

bool XavierConfiguration::isGLAntiAliasEnabled()
{
	return true;
}

unsigned int XavierConfiguration::getTimerInterval()
{
	return 25;
}

}

