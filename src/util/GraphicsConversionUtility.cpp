#include "GraphicsConversionUtility.h"

using namespace XOR;

//set the static instance to null.
GraphicsConversionUtility * GraphicsConversionUtility::_graphicsConversionUtility = 0;

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
 * protected constructor.
 */
GraphicsConversionUtility::GraphicsConversionUtility()
{
//    //fill the (co)sine tables
//    for (int i = 0; i<360; i++) {
//        float j = degressToRadians(i);
//
//        cosineValues[i] = cos(j);
//        sineValues[i]   = sin(j);
//    }
}


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
Point3D * GraphicsConversionUtility::crossProduct(Point3D * vecA, Point3D * vecB, Point3D * vecC)
{
    Point3D * vecU = *vecA - vecB;
    Point3D * vecV = *vecB - vecC;

    // the resultant is the cross product of vecU and vecV
    Point3D * resultant = new Point3D(
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
 * get cosine value (or 0).
 */
float GraphicsConversionUtility::getCosine(int deg)
{
//    deg = deg % 360;
//    float result = cosineValues[deg];

    return cos((double)deg);
}


/*
 * get sine value (or 0).
 */
float GraphicsConversionUtility::getSine(int deg)
{
//    float result = 0;
//
//    deg = deg % 360;
//    result = sineValues[deg];

    return sin((double)deg);
}


/*
 * generate DL
 */
void GraphicsConversionUtility::generateDisplayList(GLuint & displayListID, Renderable * renderable)
{
    displayListID = glGenLists(1);

    glNewList(displayListID, GL_COMPILE);
        renderable->render();
    glEndList();
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
void GraphicsConversionUtility::normalize(Point3D* points[])
{
    for (int i = 0; i<6; i++) {
        Point3D * tempPoint = points[i];

        float len = sqrtf(	tempPoint->getX() * tempPoint->getX() +
                            tempPoint->getY() * tempPoint->getY() +
                            tempPoint->getZ() * tempPoint->getZ()	);

        points[i] = new Point3D(tempPoint->getX()/len,
                                tempPoint->getY()/len,
                                tempPoint->getZ()/len   );
        delete tempPoint;
    }
}


