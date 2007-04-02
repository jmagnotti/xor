#ifndef TEXTURESCALE_H
#define TEXTURESCALE_H


#include "../geometry/Dimension2D.h"
#include "../geometry/Vector2D.h"
#include "../util/PointScale.h"


namespace XOR {

/**
 * Manages the mapping of float values in arbitrary coordinates onto texture
 * coordinates [0.0,1.0]. 
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class TextureScale
{

public:

    /**
     * Dimension mapping constants. Define which vertices to map to U and V.
     * Although not used internally, classes should define intent with these
     * constants, so that classes that are doing the actual texturing do not
     * have to guess or do unnecessary calculation.
     */
    static const int X_AND_Y = 0;
    static const int X_AND_Z = 1;
    static const int Z_AND_Y = 2;


    /**
     * Clamping rule constants. Defines what should happen when a texture extends past
     * the 1.0 bounds. TILED repeats the texture every 1.0 units. Stretch maps
     * the vertex from its range onto the texture range of 0.0f to 1.0f. Note
     * that neither of these behave as GL_CLAMP does. The current developers
     * never use it, so it is, as of yet, unsupported.
     */
    static const int TILED     = -1;
    static const int STRETCHED = -2;


    /**
     * Explicit Constructor.
     *
     * @param origin    The base value of the texture, as a u,v pair. This is
     *                  measured in arbitrary world coordinates.
     * @param size      The extent of the texture. This is measured in
     *                  arbitrary world coordinates.
     * @param mappings  A constant defining which sides should be used to
     *                  calculate the u,v mappings.
     * @param mode      A constant defining how to handle texture values larger
     *                  than 1.0f. 
     */
    TextureScale(Vector2D * origin, Dimension2D * size, const int mappping,
                 const int mode);


    /**
     * Scale the value to the range of the U scaling range. 
     *
     * @param val   The value to transform
     */
    float scaleU(float val);


    /**
     * Scale the value to the range of the V scaling range. 
     *
     * @param val   The value to transform
     */
    float scaleV(float val);


    /**
     * Returns the texture mapping rule.
     *
     * @returns The rule used for mapping u,v to x,y,z. One of
     *      TextureScale::X_AND_Y, TextureScale::X_AND_Z, or
     *      TextureScale::Y_AND_Z. 
     */
    int getMappingRule();


    /**
     * Returns the clamping rule.
     *
     * @return The rule for clamping the texture past 1.0. One of
     *         TextureScale::TILED or TextureScale::STRETCHED.
     */
    int getClampRule();


private:

    /**
     * Private constructor. 
     */
    TextureScale();

	PointScale  * _scaleU,      * _scaleV;
    Vector2D    * _scaleURange, * _scaleVRange;

	int _mapping;
	int _mode;
};

}

#endif			// TEXTURESCALE_H

