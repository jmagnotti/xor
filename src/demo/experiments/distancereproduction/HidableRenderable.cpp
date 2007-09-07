#include "HidableRenderable.h"

HidableRenderable::HidableRenderable (Renderable * renderable) 
{
	_show = true;
	_renderable = renderable;
}

void HidableRenderable::renderObject() 
{
	static String2D * s = new String2D("Hello WOrld");
		s->renderObject();
}

void HidableRenderable::setVisible(bool visible) 
{
	_show = visible;
}

