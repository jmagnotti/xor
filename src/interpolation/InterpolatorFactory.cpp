#include "InterpolatorFactory.h"


namespace XOR {

InterpolatorFactory * InterpolatorFactory::_interpolatorFactory = NULL;


/*
 * Protected Constructor
 */
InterpolatorFactory::InterpolatorFactory()
{
    _defaultInterpolator = Interpolator::LINEAR_INTERPOLATOR;
}


/*
 * Singleton Accessor
 */
InterpolatorFactory * InterpolatorFactory::GetInstance()
{
    if (_interpolatorFactory == NULL)
        _interpolatorFactory = new InterpolatorFactory();

    return _interpolatorFactory;
} 


/*
 * Sets the default interpolator for the factory
 */
void InterpolatorFactory::setDefaultInterpolator(int interpolator)
{
    _defaultInterpolator = interpolator;
}


/*
 * Returns the default interpolator
 */
Interpolator * InterpolatorFactory::getDefaultInterpolator()
{
//    cout << "Returning " << _defaultInterpolator << " interpolator" << endl;

    return getInterpolator(_defaultInterpolator);
}


/*
 * Returns the proper Interpolator
 */
Interpolator * InterpolatorFactory::getInterpolator(const int interpolator)
{
    cout << "Only returning LinearInterpolators for now" << endl;
        
    return new LinearInterpolator();

/*
    switch (interpolator)
    {
        case RK4_INTERPOLATOR:
            return new RK4Interpolator();
            break;
        case LINEAR_INTERPOLATOR:
            return new LinearInterpolator();
            break;
        case default:
      //case SQ_ROOT_INTERPOLATOR:
      //case SQUARED_INTERPOLATOR:
      //case CUBIC_INTERPOLATOR:
            return new ExponentialInterpolator(interpolator);
            break;
    }
*/

}

}

