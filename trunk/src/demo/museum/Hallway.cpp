#include "Hallway.h"
#include "DoorExtracter.h"


float abs(float a)
{
    float b = a < 0 ? -1*a : a;
    return b;
}



/*
 * Constructs a hallway connecting the two rooms' doors. Determines where the
 * finish point is relative to the starting point in order to craft the
 * appropriate route. Hallways never travel in more than one direction at a
 * time. This leads to a bit more rendering work, but makes scripted movement
 * and collision detection much simpler.
 */ 
void Hallway::build()
{
    int faceToRemove[4];
    Vector3D * start, * finish;

    start  = _start;  //+ _startVector;
    finish = _finish; //+ _finishVector;

    //Dimension3D * size = new Dimension3D(
    Vector3D * dim0 = *finish - (*start - _startVector->absoluteValue());
    Vector3D * dim1 = *finish - (*start - _startVector->absoluteValue());

    dim0->setPosition(1, _diameters->getHeight());

    if (_startVector->getX() == 0) {
        dim0->setPosition(0, _diameters->getWidth());

        faceToRemove[0] = RectangularPrism::FRONT;
        faceToRemove[1] = RectangularPrism::REAR;
    }
    else if (_startVector->getZ() == 0) {
        dim0->setPosition(2, _diameters->getDepth());
        faceToRemove[0] = RectangularPrism::RIGHT;
        faceToRemove[1] = RectangularPrism::LEFT;
    }

    dim1->setPosition(1, _diameters->getHeight());

    if (_finishVector->getX() == 0) {
        dim1->setPosition(0, _diameters->getWidth());
        faceToRemove[2] = RectangularPrism::FRONT;
        faceToRemove[3] = RectangularPrism::REAR;
    }
    else if (_finishVector->getZ() == 0) {
        dim1->setPosition(2, _diameters->getDepth());
        faceToRemove[2] = RectangularPrism::RIGHT;
        faceToRemove[3] = RectangularPrism::LEFT;
    }

    Dimension3D * size0 = new Dimension3D(dim0->toArray());
    Dimension3D * size1 = new Dimension3D(dim1->toArray());

    RectangularPrism * rp0 = new RectangularPrism(start, size0, new Paint(Color::WHITE));

    Quadrilateral3D * temp;
    temp = rp0->removeFace(faceToRemove[0]); delete temp;
    temp = rp0->removeFace(faceToRemove[1]); delete temp;

    Vector3D * rp1start = *start + size0->toVector();
    rp1start->setPosition(1, start->getY());

    RectangularPrism * rp1 = new RectangularPrism(rp1start, size1, new Paint(Color::YELLOW));

    temp = rp1->removeFace(faceToRemove[2]); delete temp;
    temp = rp1->removeFace(faceToRemove[3]); delete temp;

    // when we are rendering, we need to make sure we are rendering from min to max
    _renderable->addObject3D(rp0);
    _renderable->addObject3D(rp1);

    _renderable->compile(true);
}


/*
 * Private constructor
 */
Hallway::Hallway()
{}


/*
 * Connect the two rooms. Actual work is done in build.
 *
 * @param start     The registration point of the hallway. Values will be calculated FROM this point.
 * @param startExitVector   Values will be calculated FROM this point. 
 * @param finish    The ending point of the hallway. 
 * @param finishEntranceVector  Values will be calculated TO this point. This
 *                  is useful if the room is tilted at an angle. The calling class has a much
 *                  better idea of a value for this attack vector than the hallway can estimate.
 *                  For example, if you want to finish at [0,0,0] and approach from the front,
 *                  you could specify a finishEntranceVector of [0,0,1]. If you wanted to
 *                  approach from the top, use [0,1,0]
 * @param diameters The amount of space the hallway will occupy in directions
 *                  other than the one it is currently travelling in. For example, if the
 *                  Hallway is connecting [0,0,0] with [0,0,10] the diameters will cause the
 *                  opposing wall to extend from [width, height, 0] to [width, height, 10]. 
 * @param paint     The paint to use on the hallway.
 */
Hallway::Hallway(Vector3D * start, Vector3D * startExitVector, 
                 Vector3D * finish, Vector3D * finishEntranceVector, 
                 Dimension3D * diameters, Paint * paint)
{
    _paint = paint;

    _diameters = diameters;

    _start        = start;
    _startVector  = startExitVector;

    _finish       = finish;
    _finishVector = finishEntranceVector;

    _renderable = new Object3DCollection();

    RectangularPrism * rp_0 = new RectangularPrism(_start,  _diameters, new Paint(Color::RED));
    RectangularPrism * rp_1 = new RectangularPrism(_finish, _diameters, new Paint(Color::PINK));

    Object3D * door0 = DoorExtracter::ExtractDoor(rp_0->removeFace(RectangularPrism::LEFT));
    Object3D * door1 = DoorExtracter::ExtractDoor(rp_1->removeFace(RectangularPrism::REAR));

    _renderable->addObject3D(rp_0);
    _renderable->addObject3D(rp_1);
    _renderable->addObject3D(door0);
    _renderable->addObject3D(door1);

    build();

    _renderable->compile(true);
}


/*
 * Renders the prism 
 */
void Hallway::renderObject()
{
    _renderable->render();
}


int main(int argc, char *argv[])
{
    Controller * ctrl = Controller::GetInstance(
            InputEventHandlerFactory::GetInstance());
    ctrl->defaultConfiguration();

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

    Hallway * hallway = new Hallway( new Vector3D(10,0,20), new
            Vector3D(0,0,-1), new Vector3D(20,0,10), new Vector3D(-1, 0, 0),
            new Dimension3D(3,3,3), new Paint());


    /*
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    */
    glDisable(GL_DEPTH_TEST);
    ctrl->setModel(hallway);

    ctrl->run();

    return 0;
}





