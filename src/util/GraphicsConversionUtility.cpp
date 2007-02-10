#include "GraphicsConversionUtility.h"

using namespace XOR;

//set the static instance to null.
GraphicsConversionUtility *
GraphicsConversionUtility::_graphicsConversionUtility = 0;

//set pi
const float GraphicsConversionUtility::PI = 3.14159265358979323846;

/*
 * returns the instance.
 */
GraphicsConversionUtility * GraphicsConversionUtility::GetInstance()
{
	if (_graphicsConversionUtility == NULL)
		_graphicsConversionUtility = new GraphicsConversionUtility();

	return _graphicsConversionUtility;
}


/*
 * private constructor.
 */
GraphicsConversionUtility::GraphicsConversionUtility()
{}


/*
 * returns comparison of a and b.
 */
bool GraphicsConversionUtility::compare_f(float a, float b, float epsilon)
{
    bool result = false;
    float difference = a - b;

    if (difference <= epsilon && difference >= -epsilon)
        result = true;

    return result;
}


/*
 * evaluates the cross product of a-b X b-c.
 */
Vector3D * GraphicsConversionUtility::crossProduct(Vector3D * vecA, Vector3D *
		vecB, Vector3D * vecC)
{
    Vector3D * vecU = *vecA - vecB;
    Vector3D * vecV = *vecB - vecC;

    // the resultant is the cross product of vecU and vecV
    Vector3D * resultant = new Vector3D(
        (vecU->getY() * vecV->getZ()) - (vecU->getZ() * vecV->getY()),
        (vecU->getZ() * vecV->getX()) - (vecU->getX() * vecV->getZ()),
        (vecU->getX() * vecV->getY()) - (vecU->getY() * vecV->getX()) );

    return resultant;
}


/* 
 * changes degree to a radian value.
 */
float GraphicsConversionUtility::degressToRadians(float degree)
{
    degree *= M_PI/180.0;

    return degree;
}


/*
 * scales the value from one coordinate space to another.
 */
float GraphicsConversionUtility::mapValue(float value, float min, float max,
                                          float targetMin, float targetMax)
{
    float range = max - min;
    float targetRange = targetMax - targetMin;

    return ((value - min)/range) * targetRange + targetMin;
}	


float GraphicsConversionUtility::floatModulus(float a, int b)
{
    float c = a;

    while (c > b) 
        c -= b;

    return c;
}


/*
 * normalizes the point array.
 */
void GraphicsConversionUtility::normalize(Vector3D * points[])
{
    for (int i = 0; i<6; i++) {
        Vector3D * tempVector = points[i];

        float len = sqrtf(	tempVector->getX() * tempVector->getX() +
                            tempVector->getY() * tempVector->getY() +
                            tempVector->getZ() * tempVector->getZ()	);

        points[i] = new Vector3D(tempVector->getX()/len,
                                tempVector->getY()/len,
                                tempVector->getZ()/len   );
        delete tempVector;
    }
}


