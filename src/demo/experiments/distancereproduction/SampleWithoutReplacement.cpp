#include "SampleWithoutReplacement.h"

SampleWithoutReplacement::SampleWithoutReplacement(vector<int> population, int useCount)
{
	srand(time(NULL)); //seed the generator

	_population = population;
	_maxUse	= useCount;

	// get a descriptive on how many samples WOULD be possible,
	// to save calculations later
	_maxSamples = population.size() * _maxUse;	_samplesRemaining = _maxSamples; 
	//set all samples to 0
	for (int i=0; i<_population.size(); i++)
		_mappings[_population[i]] = 0;
}

int SampleWithoutReplacement::sample()
{
	if (_samplesRemaining > 0) {
		int result = rand() % _population.size();

		if (_mappings[_population[result]] < _maxUse) {
			--_samplesRemaining;
			_mappings[_population[result]] += 1;

			return _population[result];
		}
		else {
			return sample();
		}
	}
	else {
		return -99;
	}
}


#if 0

// testing the sampler
int main()
{
	const int MAX	  = 5;
	const int SAMPLES = 10;

	vector<int> vals;
	for (int i=0; i<MAX; i++)
		vals.push_back(i);

	SampleWithoutReplacement * swor = new SampleWithoutReplacement(vals, SAMPLES);

	for (int i=0; i<MAX*SAMPLES; i++) {
		cout << swor->sample() << "\t";
		// i+1 to care for 0
		if (! ((i+1) % 10)) cout << endl;
	}

	cout << endl;

	return 0;
}

#endif 
