#pragma once

#include "..\stdafx.h"

#if defined(WIN32)
	#if defined SCRIPT_EXPORTS
		#define DECLDIR __declspec(dllexport)
	#else
		#define DECLDIR __declspec(dllimport)
	#endif
#else
	#define DECLDIR
#endif

namespace Swtor
{
	namespace Script
	{
		class DECLDIR IPluginManager
		{
		public:

			enum Event{
				SERVER = 1,
				WORLD = 2
			};

			virtual void Register(void* handle, int event) = 0;
		protected:
		};
	}
}