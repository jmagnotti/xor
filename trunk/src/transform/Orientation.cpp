#include "Orientation.h"
namespace XOR
{

/**
 * helper for smooth movement
 */
class MovementHelper : public Action
{
public:

	MovementHelper(Orientation * orientation, float amount)
	{
		_orientation = orientation;
		_amount = amount;
	}

	void execute()
	{
		_orientation->moveAlongFocalVector(_amount);
	}

private:

	float _amount;
	Orientation * _orientation;

};


/**
 * Adds a listener
 */
void Orientation::addListener(OrientationListener * listener)
{
    _listeners.push_back(listener);
}

/**
 * Removes a listener from the pool.
 */
void Orientation::removeListener(OrientationListener * listener)
{
    bool removed = false;

    list<OrientationListener*>::iterator iter = _listeners.begin();
    list<OrientationListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == listener) {
            _listeners.erase(iter);
            removed = true;
        }
        else {
            ++iter;
        }
    }
}

/**
 * Notifies Listeners of an event (push notification)
 */
void Orientation::notifyPositionChange(Vector3D * delta, Vector3D * newPosition)
{
    // this is a little more complicated since some listeners are going to be
    // removing themselves when they get an event, so we need to use a
    // modification-safe structure. Ideally, listeners should 'mark' themselves 
    // as ready to be removed, and the subject will remove them at the end of the loop.
    list<OrientationListener*>::iterator iter = _listeners.begin();
    list<OrientationListener*>::iterator next = _listeners.begin();
    list<OrientationListener*>::iterator finish = _listeners.end();

    int which;

	//cout << "." << endl;
	//cout << newPosition->toString() << endl;
	//cout << "." << endl;

    while (iter != finish) {
        ++next;


        // which is a mask containing the sides that need to be truncated
        which = (*iter)->handlePositionChange(newPosition);

		if (which > 0) {
			if ((which & CONTAINMENT_X) == CONTAINMENT_X)
				delta->setPosition(Vector3D::X, 0);
			if ((which & CONTAINMENT_Y) == CONTAINMENT_Y)
				delta->setPosition(Vector3D::Y, 0);
			if ((which & CONTAINMENT_Z) == CONTAINMENT_Z)
				delta->setPosition(Vector3D::Z, 0);
		}
        iter = next;
    }
}

void Orientation::notifyRotationChange(float newAngle, const Vector3D * axis)
{
    // this is a little more complicated since some listeners are going to be
    // removing themselves when they get a tick, so we need to use a
    // modification-safe structure. Ideally, listeners should 'mark' themselves 
    // as ready to be removed, and the subject will remove them at the end of the loop.
    list<OrientationListener*>::iterator iter = _listeners.begin();
    list<OrientationListener*>::iterator next = _listeners.begin();
    list<OrientationListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
        ++next;
        (*iter)->handleRotationChange(newAngle, axis);
        iter = next;
    }
}

/**
 * default constructor - null orientation
 */
Orientation::Orientation()
{
	_action = NULL;
	_translated = _hasPitch = _hasRoll = _hasYaw = false;
    _currentWalkIncrement = 1.0f;
    _action = NULL;
    _translated = _hasPitch = _hasRoll = _hasYaw = false;
}

/*
 * clean up object
 */
Orientation::~Orientation()
{
	if (_action != NULL)
		delete _action;

    //FIXME: memory leak?
}

/*
 * new orientation based on existing transforms
 */
Orientation::Orientation(Translate * position, Rotate * pitch, Rotate * yaw, Rotate * roll)
{
    _translated = _hasPitch = _hasRoll = _hasYaw = false;

    _position.push_back(position);
    _pitch.push_back(pitch);
    _yaw.push_back(yaw);
    _roll.push_back(roll);
}

/*
 * new orientation based on existing transforms
 */
Orientation::Orientation(Translate * position, Vector3D * focalPoint)
{
    _position.push_back(position);
    setFocalPoint(focalPoint);
}

/*
 * clone the other's tranforms
 */
void Orientation::clone(Orientation * other)
{
    // FIXME: copy transform stacks
}

/*
 *
 */
Orientation * Orientation::clone()
{
    cout << "Orientation::clone() not implemented, returning NULL" << endl;
    // FIXME: copy transform stacks
    //
    //Orientation * cloned = new Orientation(getPosition(), getPitch(), getYaw(), getRoll());
    //cloned->_focalPoint = _focalPoint->clone();

    //return cloned;
    return NULL;
}

/*
 * pushes all subtransforms
 */
void Orientation::push()
{
	#ifdef DEBUG
		cout << "Orientation::push()" << endl;
	#endif

    // first the position
    vector<Translate*>::iterator position_iter = _position.begin();
    while (position_iter != _position.end()) {
        (*position_iter)->push();
        ++position_iter;
    }

    // order is important: roll, pitch, yaw
    vector<Rotate*>::iterator roll_iter = _roll.begin();
    while (roll_iter != _roll.end()) {
        (*roll_iter)->push();
        ++roll_iter;
    }
    vector<Rotate*>::iterator pitch_iter = _pitch.begin();
    while (pitch_iter != _pitch.end()) {
        (*pitch_iter)->push();
        ++pitch_iter;
    }
    vector<Rotate*>::iterator yaw_iter = _yaw.begin();
    while (yaw_iter != _yaw.end()) {
        (*yaw_iter)->push();
        ++yaw_iter;
    }
}

/*
 * pushes reverse of all subtransforms
 * handles _scale with bool
 */
void Orientation::pushInverse()
{
    //	cout << "start pushInv: "<< SDL_GetTicks() << endl;

    // order is important: roll, pitch, yaw
    vector<Rotate*>::iterator roll_iter = _roll.begin();
    while (roll_iter != _roll.end()) {
        (*roll_iter)->pushInverse();
        ++roll_iter;
    }
	vector<Rotate*>::iterator pitch_iter = _pitch.begin();
	while (pitch_iter != _pitch.end()) {
		(*pitch_iter)->pushInverse();
		++pitch_iter;
	}
    vector<Rotate*>::iterator yaw_iter = _yaw.begin();
    while (yaw_iter != _yaw.end()) {
        (*yaw_iter)->pushInverse();
        ++yaw_iter;
    }
    vector<Translate*>::iterator position_iter = _position.begin();
    while (position_iter != _position.end()) {
        (*position_iter)->pushInverse();
        ++position_iter;
    }
}

/*
 * pops all subtransforms
 */
void Orientation::pop()
{
	#ifdef DEBUG
    //	cout << "start pop: "<< SDL_GetTicks() << endl;
		cout << "Orientation::pop()" << endl;
	#endif
    // reverse of push

    vector<Rotate*>::iterator yaw_iter = _yaw.begin();
    while (yaw_iter != _yaw.end()) {
        (*yaw_iter)->pop();
        ++yaw_iter;
    }

    vector<Rotate*>::iterator pitch_iter = _pitch.begin();
    while (pitch_iter != _pitch.end()) {
        (*pitch_iter)->pop();
        ++pitch_iter;
    }
    vector<Rotate*>::iterator roll_iter = _roll.begin();
    while (roll_iter != _roll.end()) {
        (*roll_iter)->pop();
        ++roll_iter;
    }

	vector<Translate*>::iterator position_iter = _position.begin();
    while (position_iter != _position.end()) {
        (*position_iter)->pop();
        ++position_iter;
    }
    //	cout << "stop pop: "<< SDL_GetTicks() << endl;
}

void Orientation::setPosition(Vector3D * position)
{
    _position.push_back(Translate::CreateTranslate(position));
}

void Orientation::incrementPosition(Vector3D * position)
{
	if (_translated) {
		Vector3D * pos = *(_position[0]->toVector()) + position;
		_position[0]->setTranslation(pos);
		delete pos;
	}
	else {
		setPosition(position);
		_translated = true;
	}
}

void Orientation::incrementPosition(Vector3D * position, int milliseconds)
{
    incrementPosition(position);
}

void Orientation::setPitch(float angle)
{
    _pitch.clear();
    _pitch.push_back(Rotate::CreateRotate(angle, Rotate::PITCH));
}

void Orientation::setYaw(float angle)
{
    _yaw.clear();
    _yaw.push_back(Rotate::CreateRotate(angle, Rotate::YAW));
}

void Orientation::setRoll(float angle)
{
    _roll.clear();
    _roll.push_back(Rotate::CreateRotate(angle, Rotate::ROLL));
}

void Orientation::incrementPitch(float angle)
{
    if (_hasPitch) {
        _pitch[0]->setAngle(_pitch[0]->getAngle() + angle);
    }
    else {
        setPitch(angle);
        _hasPitch = true;
    }
}

void Orientation::incrementYaw(float angle)
{
    if (_hasYaw)
        _yaw[0]->setAngle(_yaw[0]->getAngle() + angle);
    else {
        setYaw(angle);
        _hasYaw = true;
    }
}

void Orientation::incrementRoll(float angle)
{
    if (_hasRoll)
        _roll[0]->setAngle(_roll[0]->getAngle() + angle);
    else {
        setRoll(angle);
        _hasRoll = true;
    }
}

//-- interpolated rotation incrementers
void Orientation::incrementPitch(float angle, int milliseconds)
{
    _pitch.push_back(Rotate::CreateRotate(angle, Rotate::PITCH, milliseconds));
}

void Orientation::incrementYaw(float angle, int milliseconds)
{
    _pitch.push_back(Rotate::CreateRotate(angle, Rotate::YAW, milliseconds));
}

void Orientation::incrementRoll(float angle, int milliseconds)
{
    _pitch.push_back(Rotate::CreateRotate(angle, Rotate::ROLL, milliseconds));
}

Vector3D * Orientation::getPosition()
{
    Vector3D * position = new Vector3D(0,0,0);
    vector<Translate*>::iterator iter = _position.begin();
    while (iter != _position.end()) {
        (*iter)->transform(position);
        ++iter;
    }
    return position;
}

float Orientation::getPitch()
{
    float angle = 0.0f;
    vector<Rotate*>::iterator iter = _pitch.begin();
    while (iter != _pitch.end()) {
        angle += (*iter)->getAngle();
        ++iter;
    }
    return angle;
}

float Orientation::getYaw()
{
    float angle = 0.0f;
    vector<Rotate*>::iterator iter = _yaw.begin();
    while (iter != _yaw.end()) {
        angle += (*iter)->getAngle();
        ++iter;
    }
    return angle;
}

float Orientation::getRoll()
{
    float angle = 0.0f;
    vector<Rotate*>::iterator iter = _roll.begin();
    while (iter != _roll.end()) {
        angle += (*iter)->getAngle();
        ++iter;
    }
    return angle;
}

void Orientation::moveAlongFocalVector()
{
    moveAlongFocalVector(getCurrentWalkIncrement());
}

void Orientation::moveAlongFocalVector(float distance)
{
    setCurrentWalkIncrement(distance);

    float fx, fy, fz;

    // FIXME 
    // I don't like that we are doing these calculations all the time,
    // should store and check (if getAngle == lastChecked), this way we can
    // avoid sin and cos calls. If we have a couple hundred objects running
    // along their focal vectors, this could save us a tick or two :)

    // theta (yaw) and phi (pitch) in radians
    float t = (getYaw() / 180.0f* GraphicsConversionUtility::PI);
    float p = -(getPitch() / 180.0f* GraphicsConversionUtility::PI);

    // calculate focus vector
    fx = 1.0f * cos(p) * sin(t);
    fy = 1.0f * sin(p);
    fz = 1.0f * cos(p) * cos(t);

    // adjust for given distance
    // FIXME: I think these should not be negative
    fx *= -distance;
    fy *= -distance;
    fz *= -distance;

    incrementPosition(new Vector3D(fx, fy, fz), 1000);
}

void Orientation::moveBackAlongFocalVector()
{
    moveAlongFocalVector(-getCurrentWalkIncrement());
}

void Orientation::setCurrentWalkIncrement(float distance)
{
    _currentWalkIncrement = distance;
}

/*
 * transforms --> _focus
 */
/*
 *void Orientation::updateFocalPoint()
 *{
 *    //cout << "Updating the focal point" << endl;
 *
 *    // theta and phi in radians
 *    
 *    float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
 *    float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);
 *
 *    new focal point
 *    _focalPoint->_translation[0] = _position->_translation[0] - 
 *        (_focalDistance * cos(p) * sin(t));
 *
 *    _focalPoint->_translation[1] = _position->_translation[1] - 
 *        (_focalDistance * sin(p));
 *
 *    _focalPoint->_translation[2] = _position->_translation[2] - (_focalDistance * cos(p) * cos(t));
 *}
 */

/*
 * _focus --> transforms
 */
/*
 *void Orientation::updateFromFocalPoint()
 *{
 *    // the camera can be rotated to the given focal point in
 *    // only two axes of rotations: theta and phi (not roll)
 *    // current behavior is to preserve roll upon focus reset
 *    // uncomment the following line to reset roll upon reset
 *    //_roll = 0.0;
 *
 *    // focal vector relative to position
 *    float x = _focalPoint->getX() - _position->_translation[0];
 *    float y = _focalPoint->getY() - _position->_translation[1];
 *    float z = _focalPoint->getZ() - _position->_translation[2];
 *
 *    // new rotation
 *    _phi->_angle = (asin(y / _focalDistance)) / 
 *            GraphicsConversionUtility::PI * 180.0f;
 *    _theta->_angle = (atan2(x , z) / 
 *            GraphicsConversionUtility::PI * 180.0f) - 180.0f;
 *}
 */

void Orientation::setFocalPoint(Vector3D * focalPoint)
{

    Vector3D * position = getPosition();
    float x = focalPoint->getX() - position->getX();
    float y = focalPoint->getY() - position->getY();
    float z = focalPoint->getZ() - position->getZ();
    float distance = sqrt(pow(focalPoint->getX() - position->getX(), 2.0f)
            +pow(focalPoint->getY()- position->getY(), 2.0f)
            +pow(focalPoint->getZ() - position->getZ(), 2.0f));
    float pitch = (asin(y / distance)) / GraphicsConversionUtility::PI * 180.0f;
    float yaw = (atan2(x, z) / GraphicsConversionUtility::PI * 180.0f) - 180.0f;
    setPitch(pitch);
    setYaw(yaw);
}

/*
 * print member info
 */
void Orientation::print()
{
    Vector3D * position = getPosition();
    cout << "x="<< position->getX() << "  y="<< position->getY() << "  z="
            << position->getZ()<< endl;
    cout << "pitch="<< getPitch() << "  yaw="<< getYaw() << "  roll="
            << getRoll() << endl;
    return;
    /*
     float distance = sqrt(
     pow(_focalPoint->_translation[0] - _position->_translation[0], 2.0f) +
     pow(_focalPoint->_translation[1] - _position->_translation[1], 2.0f) +
     pow(_focalPoint->_translation[2] - _position->_translation[2], 2.0f));

     cout << endl << "---Transformable Information " << this << " ---" << endl;

     cout << "focal distance=" << _focalDistance << endl;
     cout << "real distance="  << distance << endl;

     cout << "pos_x="     << _position->_translation[0] << 
     "pos_y="     << _position->_translation[2] <<
     "pos_z="     << _position->_translation[2] << endl;

     cout << "focus_x="     << _focalPoint->_translation[0] << 
     "focus_y="     << _focalPoint->_translation[1] <<
     "focus_z="     << _focalPoint->_translation[2] << endl;

     cout << "theta="   << _theta->_angle << 
     "phi="     << _phi->_angle   <<
     "roll="    << _roll->_angle  << endl;;
     */
}

/*
 * reset the transforms
 */
void Orientation::toIdentity()
{
    // FIXME: fix memory leak
    _position.clear();
    _pitch.clear();
    _yaw.clear();
    _roll.clear();
}

void Orientation::startMovingAlongFocalVector(float distance)
{
    setCurrentWalkIncrement(distance);

    if (_action != NULL) {
        //_action->incrementAmount(distance);
    }
    else {
        _action = new ContinuousAction(new MovementHelper(this, distance));
        _action->execute();
    }

}

void Orientation::startMovingAlongFocalVector()
{
    startMovingAlongFocalVector(getCurrentWalkIncrement());
}

float Orientation::getCurrentWalkIncrement()
{
    return _currentWalkIncrement;
}

void Orientation::transform(Vector2D * position)
{
	cout << "EMPTY" << endl;
	//if (_action != NULL) {
		//_action->stopExecuting();
		//delete _action;
	//}
	//_action = new ContinuousAction(new MovementHelper(this, getCurrentWalkIncrement()));
	//_action->execute();
}

void Orientation::stopMovingAlongFocalVector()
{
	if (_action != NULL) {
		_action->stopExecuting();
		delete _action;
		_action = NULL;
	}
}

void Orientation::transform(Dimension2D * size) { }
void Orientation::transform(Vector3D * position) { }
void Orientation::transform(Dimension3D * size) { }

}

