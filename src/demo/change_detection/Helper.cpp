#include "Helper.h"

using namespace std;

bool Helper::_seeded = false;

/*
 * returns the index associated with the given value for the given vector
 * returns -1 if the needle was not in the haystack
 */
int Helper::FindInVec(vector<int> haystack, int needle)
{
	int ret = -1;

	for(int i=0; i<haystack.size() && ret < 0; i++) {
		if (haystack[i] == needle)
			ret = i;	
	}
	return ret;
}

void Helper::Reorder(vector<int> * a)
{
	int size = a->size();
	for(int i=0;i<size;i++) {
		int sample_size = size - i;
		int random = rand()	% sample_size;
		int t= a->at(size-(i+1));
		a->at(size-(i+1)) = a->at(random);
		a->at(random) = t;
	}

	//for(int i=0; i<a->size(); i++)
	//cout << a->at(i) << endl;

}

void Helper::Reorder(vector<Trial*> * a, int seed)
{
	srand(seed);
	Reorder(a);
}


void Helper::Reorder(vector<Trial*> * a)
{
	int size = a->size();
	for(int i=0;i<size;i++) {
		int sample_size = size - i;
		int random = rand()	% sample_size;
		Trial * t= a->at(size-(i+1));
		a->at(size-(i+1)) = a->at(random);
		a->at(random) = t;
	}

	//for(int i=0; i<a->size(); i++)
	//cout << a->at(i) << endl;

}

void Helper::SampleWOReplacement(vector<int> pop, vector<int> * sample, int n)
{

	int size = pop.size();

	for(int i=0; i<n; i++) {
		int sample_size = n - i;
		int random = rand()	% (size - i);

		sample->push_back(pop[random]);

		int t = pop[(size-(i+1))];
		pop[size-(i+1)] = pop[random];
		pop[random] = t;
	}

	/*
	cout << "Initial Sample" << endl;
	for(int i=0; i<n; i++)
		cout << sample->at(i) << endl;
	*/
}

void Helper::FreshSampleWOReplacement(vector<int> pop, vector<int> * sample, vector<int> stale, int n)
{
	int size = pop.size();

	for(int i=0; i<n; i++) {
		int sample_size = n - i;
		int random;
		do {
			random = rand()	% (size - i);
		} while (find(stale.begin(), stale.end(), pop[random]) != stale.end());

		sample->push_back(pop[random]);

		int t = pop[(size-(i+1))];
		pop[size-(i+1)] = pop[random];
		pop[random] = t;
	}

	/*
	cout << "Fresh Sample" << endl;
	for(int i=0; i<n; i++)
		cout << sample->at(i) << endl;
	*/
}

void Helper::PrintVector(vector<int> a) {
	for (int i=0; i<a.size(); i++)
		cout << "\t" << a[i];

	cout << endl;
}

void Helper::SeedGenerator()
{
	if (! _seeded) { srand(time(NULL)); _seeded = true; }
}

/**
int main (int argc, char * argv[]) {
	
	srand(time(NULL));
	vector<int> pop;
	vector<int> sample;
	for(int i=0; i<20; i++)
		pop.push_back(i);

	Helper::SampleWOReplacement(pop, &sample, pop.size());

	for(int i=0; i<sample.size(); i++)
		cout << sample[i] << endl;

	return 0;
}
**/
