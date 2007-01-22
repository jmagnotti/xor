#ifndef RESHAPESKELETON_H
#define RESHAPESKELETON_H


#include "Reshape.h"
#include "ReshapeEvent.h"


namespace XOR {

/*
 * impl for Reshape
*/
class ReshapeSkeleton : public Reshape
{

public:

      
    static ReshapeSkeleton * GetInstance();

    void fireEvent(ReshapeEvent * event);


private:

    ReshapeSkeleton();

    static ReshapeSkeleton * _reshapeSkeleton;

};

}

#endif          // RESHAPESKELETON_H

