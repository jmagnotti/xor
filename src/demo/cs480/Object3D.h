#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "SDL_opengl.h" 
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
/*
 *  Object3D.h
 *  CS480FinalProject
 *
 *  Created by Everette on 4/7/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

class Object3D
{
public:
	static const int WIRE_FRAME = 0;
	static const int FILLED = 1;
};

#endif //OBJECT3D_H