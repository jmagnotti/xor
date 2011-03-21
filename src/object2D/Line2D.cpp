#include "Line2D.h"

namespace XOR {

Line2D::Line2D()
{}

Line2D::~Line2D()
{
    delete _paint;
    delete _start;
    delete _finish;
}

Line2D::Line2D(Vector2D * p0, Vector2D * p1)
{
    _paint = new Paint();

	_start  = p0;
	_finish = p1;
}

Line2D::Line2D(Vector2D * p0, Vector2D * p1, Paint * paint)
{
	_paint = paint;

	_start  = p0;
	_finish = p1;
}

void Line2D::renderObject()
{
    Vector3D * paintWeights = new Vector3D(0,0,1); 

    glBegin(GL_LINES);
        _paint->activateColorAtPosition(paintWeights);
        glVertex2fv(_start->toArray());

        paintWeights->setPosition(1,1);
        paintWeights->setPosition(0,1);
        _paint->activateColorAtPosition(paintWeights);

        glVertex2fv(_finish->toArray());
    glEnd();

    delete paintWeights;
}

void Line2D::setPaint(Paint * paint)
{
    _paint = paint;
}

Dimension2D * Line2D::getDimension()
{
    GraphicsConversionUtility * gcu = GraphicsConversionUtility::GetInstance();
    return new Dimension2D(gcu->fabs(_start->getX() - _finish->getX()), gcu->fabs(_start->getY() - _finish->getY()));
}

Vector2D * Line2D::getBaseVector() {
    return _start->clone();
}

}
