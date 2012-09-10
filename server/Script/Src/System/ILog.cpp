#include "ILog.h"
#include <Shared/omp_mutex.h>

namespace Swtor { namespace System
{
	#pragma data_seg(".shared")
	ILog* ILog::mInstance = nullptr;
	static char gLocked = 0;
	#pragma data_seg()

	bool ILog::AcquireLock()
	{
		if(gLocked)
			return false;
#pragma omp critical (ILog)
		{
			if(gLocked & 1)
				return false;
			gLocked = 1;
		}
		return true;
	}

	void ILog::ReleaseLock()
	{
		gLocked = 0;
	}
}
}