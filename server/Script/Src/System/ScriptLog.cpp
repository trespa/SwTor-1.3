#include "ILog.h"

#if defined(WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C"
{
	EXPORT void Debug(const char* message)
	{
		Swtor::System::ILog::Debug(message);
	}

	EXPORT void Error(const char* message)
	{
		Swtor::System::ILog::Error(message);
	}

	EXPORT void Print(const char* message)
	{
		Swtor::System::ILog::Print(message);
	}
};