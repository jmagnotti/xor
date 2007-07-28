#include "../../xor.h"
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace XOR;
using namespace std;

string itoa(int value, int base);


int main() 
{
	MulticastUserSocket misocketz;
	int number = 0;
	string snum;
	
	while(1) {
		snum = itoa(number, 10);
//		cout << "Sending: " << snum << endl;
		misocketz.send(snum);	
		number++;
	}
}


/**
 * C++ version std::string style "itoa":
 */
string itoa(int value, int base) {

	enum { kMaxDigits = 35 };
	std::string buf;
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.

	
	// check that the base if valid
	if (base < 2 || base > 16) return buf;
	int quotient = value;
	
	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );
	
	// Append the negative sign for base 10
	if ( value < 0 && base == 10) buf += '-';

	std::reverse( buf.begin(), buf.end() );
	return buf;
}
