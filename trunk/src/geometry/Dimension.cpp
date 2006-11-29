#include "Dimension.h"

namespace XOR {

/*
 * Clone function.
 */
void Dimension::clone(Dimension * other)
{
    int size = getDimensionality();

    if (other->getDimensionality() > size)
        size = other->getDimensionality();

    for (int i=0; i < size; i++)
        _dimension[i] = other->_dimension[i];
}

void Dimension::scale(float scale)
{
    for (int i=0; i < getDimensionality(); i++)
        _dimension[i] *= scale;
}


/*
 * Returns the largest value in the dimension
 */
float Dimension::getLargestSize()
{
    float max = _dimension[0];

    for (int i=1; i < getDimensionality(); i++)
        if (_dimension[i] > max)
            max = _dimension[i]; 
        
    return max;
}


/*
 * Returns the largest value in the dimension
 */
float Dimension::getSmallestSize()
{
    float min = _dimension[0];

    for (int i=1; i < getDimensionality(); i++)
        if (_dimension[i] < min)
            min = _dimension[i]; 

    return min;
}


/*
 * Returns the dimension formatted as an array
 */
float * Dimension::toArray()
{
	return _dimension;
}

}

