#ifndef FRAMESPERSECONDCOUNTER_H
#define FRAMESPERSECONDCOUNTER_H

#include <stdlib.h>
#include  <iostream> //debugging

#include "../event/timer/Timer.h"
#include "../event/timer/TimerListener.h"
#include "../core/Controller.h"
#include "../object2D/String2D.h"
#include "../object3D/Point3D.h"


using namespace std;

namespace XOR {


/**
 * An easy way to get an FPS counter. Sports the ability to render at a given 
 * Screen coordinate, or in the Title Bar of the window (won't show up in 
 * full screen mode)
 */
class FramesPerSecondCounter : public TimerListener
{

public:

    /**
     *  Display modes to pass to setDisplayMode
     */
    static const int TITLE_BAR = 0;
    static const int ON_SCREEN = 1;

    FramesPerSecondCounter();

    virtual ~FramesPerSecondCounter();

    void setDisplayMode(int displayMode);
    void setPosition(Point3D * pos);
    void setLabel(char * text);
    void setLabel(String2D * text);
    void handleTick();
    
protected:

    String2D * _displayText;
    
    int     _displayMode;
    int     _frameCounter;
    int     _lastTimeUpdate;

};

}


#endif          // FRAMESPERSECONDCOUNTER_H

