#ifndef WINDOW_H
#define WINDOW_H


#include <list>
#include <iostream>

#include "../../include/SDL.h"

#include "../event/reshape/ReshapeListener.h"
#include "../geometry/Dimension2D.h"
#include "../geometry/Vector2D.h"


using namespace std;

namespace XOR {

/**
 * Represents the current state of the window.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Window
{

public:

    static const char * DEFAULT_WINDOW_TITLE;

    static const int DEFAULT_WINDOW_X;
    static const int DEFAULT_WINDOW_Y;

    static const int DEFAULT_WINDOW_WIDTH;
    static const int DEFAULT_WINDOW_HEIGHT;


    /**
     * Default constructor.
     * Builds a window according to the preset defaults.
     */
    Window();
    Window(Vector2D * origin, Dimension2D * size, char * title);


    /*
     * Adds a listener
     */
    void addListener(ReshapeListener * rl);


    /**
     * Generates a reshape event from the SDL_Event
     */
    void generateEvent(SDL_Event * event);


    /**
     * Returns a constant reference to the dimension of this window.
     */
    Dimension2D * getSize() const;


    /**
     * Notifies listeners of the reshape event
     */
    void notifyListeners(ReshapeEvent * event);


    /**
     * Remove a listener from the pool. Should be re-written to use "find" instead
     * of iterating ourselves.
     */
    void removeListener(ReshapeListener * rl);


    /**
     * Sets the title of the window
     */
    void setTitle(char * title);


    /*
     * Called to trigger a reshape event with the current settings. Use for
     * setting up new window contexts that don't already trigger a reshape
     * event.
     */
    static void ForceReshape();


private:

    /**
     * constructs the window
     */
    void build(Vector2D * origin, Dimension2D * size, char * title);

	Vector2D    * _origin;
	Dimension2D *   _size;

    list<ReshapeListener*> _listeners;

	char *   _title;

    static SDL_Event _reshape;
};

}

#endif			// WINDOW_H

