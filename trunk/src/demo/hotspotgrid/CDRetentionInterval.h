#ifndef CD_RETENTION_INTERVAL_H
#define CD_RETENTION_INTERVAL_H

#include <vector>
#include "CDState.h"

#include "CDSecondDisplay.h"

using namespace std;

class CDRetentionInterval : public CDState 
{

public:

	static CDRetentionInterval * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

	CDRetentionInterval();

	static CDRetentionInterval * _state;
};

#endif			//CD_RETENTION_INTERVAL_H

