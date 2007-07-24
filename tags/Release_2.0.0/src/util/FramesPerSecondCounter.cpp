#include "FramesPerSecondCounter.h"


namespace XOR {


/*
 * destructor
 */
FramesPerSecondCounter::~FramesPerSecondCounter()
{
    Controller::GetInstance(NULL)->getTimer()->removeListener(this);
    delete _displayText;
}


/*
 * Default constructor
 */
FramesPerSecondCounter::FramesPerSecondCounter()
{
    Controller::GetInstance(NULL)->getTimer()->addListener(this);
    
    _displayText = new String2D("FPS: n/a");

    _displayMode    = TITLE_BAR;
    _frameCounter   = 0;
    _lastTimeUpdate = 0;
}


/*
 * sets the display mode
 */
void FramesPerSecondCounter::setDisplayMode(int displayMode)
{
    _displayMode = displayMode;
}

/*
 * Sets the on screen position of the FPS counter.
 * this is the top left corner.
 */
void FramesPerSecondCounter::setPosition(Point3D * pos)
{}


/*
 * Sets what is displayed by the counter before the FPS count
 */
void FramesPerSecondCounter::setLabel(char * text)
{
    _displayText->setText(text);
}


/*
 * Sets what is displayed by the counter before the FPS count
 */
void FramesPerSecondCounter::setLabel(String2D * text)
{
    _displayText = text;
}


/*
 * Called by timer ticks
 */
void FramesPerSecondCounter::handleTick()
{
    // callback to the timer to get some info beyond just the tick event
    Timer * timer = Controller::GetInstance()->getTimer();

    char s [50];
    _frameCounter++;
    
    int time = timer->getElapsedTime();
    
    // fps display technique from lighthouse tutorials
    if (time - _lastTimeUpdate >= 1000) {

        sprintf(s, "nothing left to do but play FPS: %4.2f",
            _frameCounter * 1000.0/(time - _lastTimeUpdate));

        _displayText->setText(s);
            
        if (_displayMode == ON_SCREEN) {
            _displayText->render();
        }
        else if (_displayMode == TITLE_BAR) {
            Controller::GetInstance()->getWindow()->setTitle(
                    _displayText->getText());
        }

        _lastTimeUpdate = time;
        _frameCounter	= 0;
    }
}

}

