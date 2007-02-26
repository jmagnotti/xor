#ifndef KEYHANDLER_H
#define KEYHANDLER_H


#include <map>
#include "../../xor.h"


using namespace std;
using namespace XOR;

/**
 *
 */
class KeyHandler : public DefaultKeyboardListener
{

public:

    /**
     * Default Constructor
     */
    KeyHandler(Controller * ctrl);


    /**
     * moves the camera left by 1 over 1 second
     */
    void handleKey_a();


    /**
     * moves the camera down by 1 over 1 second
     */
    void handleKey_c();


    /**
     * moves the camera right by 1 over 1 second
     */
    void handleKey_d();


    /**
     * moves the camera up by 1 over 1 second
     */
    void handleKey_e();


    /**
     * moves the camera out by 1 over 1 second
     */
    void handleKey_s();
    void handleKey_P();


    /**
     * moves the camera in by 1 over 1 second
     */
    void handleKey_w();

    /**
     * Focal point manipulators
     */
    void handleKey_D();
    void handleKey_A();

private:

	Controller * _controller;

    map<const char*,TimedInterpolation*>    _timers;
    map<const char*,Vector3D*> _vectors;

};

#endif			// KEYHANDLER_H

