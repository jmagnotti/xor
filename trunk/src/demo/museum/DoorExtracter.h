#ifndef DOOREXTRACTER_H
#define DOOREXTRACTER_H


#include "../../xor.h"


using namespace XOR;

/**
 * Utility class for carving holes in a Quadrilateral3D.
 *
 * @author John Magnotti
 * @version 1.0
 */
class DoorExtracter
{

public:

    /**
     * Returns an Object3D representing the quad with a door cut out of it. The
     * memory allocated for the Quadrilateral3D is left untouched. The calling
     * class is responsible for properlyi reclaiming it.
     */
    static Object3D * ExtractDoor(Quadrilateral3D * face);


    /**
     * Set the height of all future doors created by this extracter
     */
    static void SetDoorHeight(float height);


    /**
     * Set the width of all future doors created by this extracter
     */
    static void SetDoorWidth(float width);


private:

    /**
     * Private Constructor. Not needed, just a utility class.
     */
    DoorExtracter();

	static float _doorHeight, _doorWidth;
};

#endif			// DOOREXTRACTER_H

