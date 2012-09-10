#pragma once
#pragma unmanaged

#if defined _WIN32
	#if defined SCRIPT_EXPORTS
		#define DECLDIR __declspec(dllexport)
	#else
		#define DECLDIR __declspec(dllimport)
	#endif
#else
	#define DECLDIR
#endif // WIN32

#include "StdAfx.h"
using namespace std;

namespace Swtor { namespace System
{
	class DECLDIR ILog
	{
	public:

		enum Level
		{
			NONE,
			LOW,
			VERBOSE
		};

		static inline ILog* GetInstance()
		{
			return mInstance;
		}
		static bool AcquireLock();
		static void ReleaseLock();

		virtual void DoPrint(const char* pMessage, size_t pLength) = 0;
		virtual void DoDebug(const char* pMessage, size_t pLength) = 0;
		virtual void DoError(const char* pMessage, size_t pLength) = 0;

		virtual void DoSetLevel(ILog::Level pLevel) = 0;
		virtual void DoFlush() = 0;

		/**
		 * Overrides for std::string
		 */

		static inline void Print(const string& pMessage)
		{
			GetInstance()->DoPrint(pMessage.c_str(), pMessage.length());
		}
		static inline void Debug(const string& pMessage)
		{
			GetInstance()->DoDebug(pMessage.c_str(), pMessage.length());
		}
		static inline void Error(const string& pMessage)
		{
			GetInstance()->DoError(pMessage.c_str(), pMessage.length());
		}

		/**
		 * Template overrides for static strings
		 */

	template<size_t Size>
		static inline void Print(const char (&pMessage)[Size])
		{
			GetInstance()->DoPrint(pMessage, Size);
		}
	template<size_t Size>
		static inline void Debug(const char (&pMessage)[Size])
		{
			GetInstance()->DoDebug(pMessage, Size);
		}
	template<size_t Size>
		static inline void Error(const char (&pMessage)[Size])
		{
			GetInstance()->DoError(pMessage, Size);
		}

		/**
		 * Overrides for regular strings
		 */

		static inline void Print(const char* pMessage)
		{
			GetInstance()->DoPrint(pMessage, strlen(pMessage));
		}
		static inline void Debug(const char* pMessage)
		{
			GetInstance()->DoDebug(pMessage, strlen(pMessage));
		}
		static inline void Error(const char* pMessage)
		{
			GetInstance()->DoError(pMessage, strlen(pMessage));
		}

		static inline void SetLevel(ILog::Level pLevel)
		{
			GetInstance()->DoSetLevel(pLevel);
		}

		/**
			* Flushes all gathered data into the log stream
			*/
		static inline void Flush()
		{
			GetInstance()->DoFlush();
		}

	protected:

		static ILog* mInstance;
	};
}
}