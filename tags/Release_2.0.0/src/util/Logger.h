#ifndef LOGGER_H
#define LOGGER_H


#include <iostream>

using namespace std;

namespace XOR {

/**
 *
 */
class Logger
{

public:

    
    void decrementTabLevel();


    
    static Logger * GetInstance();


    
    void incrementTabLevel();


    
    void printTabs();


    
    void setTabLevel(int level);


private:

    Logger();

	static Logger * _logger;
	int _tabLevel;
};

}

#endif			// LOGGER_H

