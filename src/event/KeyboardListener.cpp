#include "KeyboardListener.h"

namespace XOR {

KeyboardListener::KeyboardListener()
{
    Keyboard::GetInstance()->addListener(this);
}

}

