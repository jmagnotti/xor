#include "Reshape.h"


namespace XOR {

Reshape::Reshape()
{}

void Reshape::generateEvent(SDL_Event * event)
{
    fireEvent(ReshapeEvent::ConstructInstance(new Dimension2D(event->resize.w, event->resize.h)));
}


void Reshape::notifyListeners(ReshapeEvent * event)
{
    list<ReshapeListener*>::iterator iter   = listeners.begin();
	list<ReshapeListener*>::iterator next   = listeners.begin();
    list<ReshapeListener*>::iterator finish = listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handleReshape(event);
        iter = next;
    }

}

/*
 * Adds a listener
 */
void Reshape::addListener(ReshapeListener * rl)
{
    listeners.push_back(rl);
}


/*
 * Remove a listener from the pool
 */
void Reshape::removeListener(ReshapeListener * rl)
{
    cout << "Removing: " << rl << endl;
    bool removed = false;

    list<ReshapeListener*>::iterator iter   = listeners.begin();
    list<ReshapeListener*>::iterator finish = listeners.end();

    while (!removed && iter != finish) {
        if (*iter == rl) {
            listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }
}

}

