#include "LinearInterpolator.h"


namespace XOR {

/*
 * Default Constructor
 */
LinearInterpolator::LinearInterpolator()
{
//    cout << "Compiled with lots of debugging" << endl;
    _steps = new vector<float>(); 
}


/*
 * Calculates the next value in the sequence and stores it in value
 */
void LinearInterpolator::next()
{
    vector<float*>::iterator vals_iter   = _values->begin();
    vector<float*>::iterator vals_finish = _values->end();

    vector<float>::iterator step_iter   = _steps->begin();
    vector<float>::iterator step_finish = _steps->end();

    while (vals_iter != vals_finish && step_iter != step_finish) {
        //cout << "Old value: " << (*(*vals_iter)) << " Step amount: " << (*step_iter) << endl; 
        (*(*vals_iter)) += (*step_iter);    // the actual work
        //cout << "\tNew value: " << (*(*vals_iter)) << endl;
        vals_iter++; step_iter++;
    }
}


/*
 * single value step calculation
void LinearInterpolator::setScale(float & in, float & out, int numSteps)
{
    _values->push_back(in);
    
    _steps->push_back( (out / in) / (float)numSteps);
} 
*/

/*
 * clear out the interpolator
 */
void LinearInterpolator::reset()
{
    _steps->clear();

    //delete _final;
    //_final = new vector<float>();
    
    // don't delete the old _values as that would hose the object they reference
    _values = new vector<float*>();
}



void LinearInterpolator::finish()
{
    vector<float*>::iterator vals_iter   = _values->begin();
    vector<float*>::iterator vals_finish = _values->end();

    vector<float>::iterator end_iter   = _final->begin();
    vector<float>::iterator end_finish = _final->end();
    
    while(vals_iter != vals_finish && end_iter != end_finish) {
        *(*vals_iter) = *end_iter;
        ++vals_iter; ++end_iter;
    }
}


/*
 * Calculates the step amount
 */
void LinearInterpolator::setScale(vector<float*> & in, vector<float> & out, int numSteps)
{
    _values = &in;       // grab the references for later
    _final  = &out;

    vector<float*>::iterator in_iter   = in.begin();
    vector<float*>::iterator in_finish = in.end();

    vector<float>::iterator out_iter   = out.begin();
    vector<float>::iterator out_finish = out.end();

    while (in_iter != in_finish && out_iter != out_finish) {
        cout << "src: " << (**in_iter) << " target: " << (*out_iter) << " steps: " << numSteps << endl;
            
        _steps->push_back( ( (*out_iter) - (*(*in_iter)) ) / numSteps);

        cout << "\tstep size: " << ( (*out_iter) - (*(*in_iter)) ) / numSteps << endl;

        in_iter++; out_iter++;
        cout << endl << endl << endl;
    }
}


/*
 * getter to aid type reflection
 */
const int LinearInterpolator::getType()
{
    return Interpolator::LINEAR_INTERPOLATOR;
}

}
