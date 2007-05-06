#ifndef XAVIERCONFIGURATION_H
#define XAVIERCONFIGURATION_H


#include <SDL/SDL.h>

#include "../transform/CoordinateSystem.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"
#include "../event/EventFactory.h"
#include "../event/InputEventProxyFactory.h"
#include "../paint/Color.h"

#include "Camera.h"
#include "Window.h"
   

namespace XOR {

/**
 *
 */
class XavierConfiguration
{

public:

    
    XavierConfiguration();

    
    virtual const float * getBackgroundColor();

    
    virtual int getColorDepth();

    
    virtual CoordinateSystem * getCoordinateSystem() const;


    virtual EventFactory * getEventFactory() const;

    
    virtual double getFarClip();

    
    virtual double getFieldOfView();

    
    virtual const float * getGLFogColor();

    
    virtual int getGLFogEnd();

    
    virtual int getGLFogMode();

    
    virtual int getGLFogStart();

    
    virtual int getGLShadeModel();

    
    virtual double getNearClip();

    
    virtual unsigned int getTimerInterval();

    
    virtual Uint32 getVideoFlags();

    
    virtual int getWallMode();

    
    virtual Vector2D * getWallOffset() const;

    
    virtual Vector2D * getWindowPosition() const;

    
    virtual Dimension2D * getWindowSize() const;

    
    virtual const char * getWindowTitle() const;

    
    virtual bool isFullScreen();


    virtual bool isGLAntiAliasEnabled();


    virtual bool isGLBlendEnabled();

    
    virtual bool isGLDepthTestEnabled();

    
    virtual bool isGLFogEnabled();

    
    virtual bool isGLTextureEnabled();

};

}

#endif			// XAVIERCONFIGURATION_H

