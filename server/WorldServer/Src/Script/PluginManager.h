/*#pragma once

#include <list>
#include <tuple>
#if defined(WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace Swtor
{
    namespace Script
    {
		class Plugin;
        /**
		* Plugin manager
		
		class PluginManager
		{
		public:

			typedef std::list<Plugin*> Listeners;

			PluginManager()
			{
			}

			~PluginManager()
			{
			}

			static PluginManager& GetInstance();

			void Initialize();
			void Free();

			//void AddShard(Game::IWorld* world);

			void Register(void* plugin, int event);

		private:

			std::list<std::tuple<Plugin*,std::string>> mPlugins;
#if defined(WIN32)
std::list<HMODULE>  mSharedObjects;
#else
std::list<void*> mSharedObjects;
#endif

			Listeners mServerListeners;
			Listeners mWorldListeners;

			static PluginManager* mInstance;
		};
    }
}
*/
