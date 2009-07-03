#include "Helper.h"

using namespace std;

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
