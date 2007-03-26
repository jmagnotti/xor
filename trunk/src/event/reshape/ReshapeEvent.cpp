#include "ReshapeEvent.h"


namespace XOR {

ReshapeEvent * ReshapeEvent::_reshapeEvent = 0;

ReshapeEvent::ReshapeEvent()
{}

ReshapeEvent::ReshapeEvent(Dimension2D * size)
{
    _size = size;
}


/*
 * construct from SDL_Event
 */
ReshapeEvent * ReshapeEvent::ConstructInstance(SDL_Event * event)
{
	return ReshapeEvent::ConstructInstance(
			new Dimension2D(event->resize.w, event->resize.h));
}


/*
 * construct from Dimension2D
 */
ReshapeEvent * ReshapeEvent::ConstructInstance(Dimension2D * size)
{
    return new ReshapeEvent(size);
}


/*
 * height of the resize
 */
int ReshapeEvent::getHeight()
{
    return (int)(_size->getHeight());
}


/*
 * width of the resize
 */
int ReshapeEvent::getWidth()
{
    return (int)(_size->getWidth());
}

Dimension2D * ReshapeEvent::getSize() const
{
    return _size;
}

}

