#ifndef CD_RETENTION_INTERVAL_H
#define CD_RETENTION_INTERVAL_H

#include <vector>
#include "CDState.h"

#include "CDSecondDisplay.h"
#include "SerialPortTimer.h"

using namespace std;

class CDRetentionInterval : public CDState 
{

public:

	static CDRetentionInterval * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

	CDRetentionInterval();
    int ticksRemaining;

	static CDRetentionInterval * _state;
};

#endif			//CD_RETENTION_INTERVAL_H

