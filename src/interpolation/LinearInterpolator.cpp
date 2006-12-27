#include "LinearInterpolator.h"


namespace XOR {

/*
 * Default Constructor
 */
LinearInterpolator::LinearInterpolator()
{
//    cout << "Compiled with lots of debugging" << endl;
    _steps = new list<float>(); 
}


/*
 * Calculates the next value in the sequence and stores it in value
 */
void LinearInterpolator::next()
{
    list<float*>::iterator vals_iter   = _values->begin();
    list<float*>::iterator vals_finish = _values->end();

    list<float>::iterator step_iter   = _steps->begin();
    list<float>::iterator step_finish = _steps->end();

    while (vals_iter != vals_finish && step_iter != step_finish) {
        cout << "Old value: " << (*(*vals_iter)) << " Step amount: " << (*step_iter) << endl; 

        (*(*vals_iter)) += (*step_iter);    // the actual work

        cout << "\tNew value: " << (*(*vals_iter)) << endl;
        vals_iter++; step_iter++;
    }
}


/*
 * single value step calculation
 */
void LinearInterpolator::setScale(float & in, float & out, int numSteps)
{
    
} 


/*
 * clear out the interpolator
 */
void LinearInterpolator::reset()
{
    _steps->clear();

    // don't delete the old _values
    _values = new list<float*>();
}


/*
 * Calculates the step amount
 */
void LinearInterpolator::setScale(list<float*> * in, list<float*> * out, int numSteps)
{
    _values = in;

    list<float*>::iterator in_iter   = in->begin();
    list<float*>::iterator in_finish = in->end();

    list<float*>::iterator out_iter   = out->begin();
    list<float*>::iterator out_finish = out->end();

    while (in_iter != in_finish && out_iter != out_finish) {
        cout << "src: " << (**in_iter) << " target: " << (**out_iter) << " steps: " << numSteps << endl;
            
        _steps->push_back( ( (*(*out_iter)) - (*(*in_iter)) ) / numSteps);

        cout << "\tstep size: " << ( (*(*out_iter)) - (*(*in_iter)) ) / numSteps << endl;
        in_iter++; out_iter++;
    }

}

}

