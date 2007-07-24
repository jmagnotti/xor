#include "Logger.h"

namespace XOR {

Logger * Logger::_logger = NULL;


Logger * Logger::GetInstance()
{
    if (_logger == NULL)
        _logger = new Logger();

    return _logger;
}

void Logger::setTabLevel(int level)
{
    _tabLevel = level;
}

void Logger::incrementTabLevel()
{
    _tabLevel++;
}

void Logger::decrementTabLevel()
{
    _tabLevel--;
}

void Logger::printTabs()
{
	//cout << "printing " << _tabLevel << " tabs!" << endl;
	
    int i=0;
    while (i < _tabLevel) {
        cout << "........";
        i++;
    }
}

Logger::Logger()
{
    _tabLevel = 0;
}

}
