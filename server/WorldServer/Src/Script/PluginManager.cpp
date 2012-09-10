/*#include <Script/PluginManager.h>
#include <boost/filesystem.hpp>
#include <System/Log.h>
#include <string>
#include <iostream>

namespace Swtor { namespace Script
{
	using namespace std;
	using namespace boost;

	//---------------------------------------------------------------------------------------
	PluginManager* PluginManager::mInstance = nullptr;
	//---------------------------------------------------------------------------------------
	PluginManager& PluginManager::GetInstance()
	{
		if(mInstance == nullptr)
		{
			mInstance = new PluginManager;
			mInstance->Initialize();
		}
		return *mInstance;
	}
	//---------------------------------------------------------------------------------------
	void PluginManager::Initialize()
	{
		filesystem::path dir("./Script");

		if(!filesystem::exists(dir))
			filesystem::create_directory(dir);

		vector<filesystem::path> files;

		copy(filesystem::directory_iterator(dir),
			filesystem::directory_iterator(), back_inserter(files));

		for(auto it = files.begin(); it != files.end(); it++)
		{
#if defined(WIN32)
			if(it->extension() == ".dll")
			{
				HMODULE dll = LoadLibraryA((*it).string().c_str());
				if(dll != NULL)
				{
					typedef Plugin* (*RegisterScripts)(IPluginManager*);
					RegisterScripts pfnLoad = (RegisterScripts)GetProcAddress(dll, "LoadPlugin");

					if(pfnLoad)
					{
						mPlugins.push_back(std::make_tuple(pfnLoad(this), it->filename().string()));
						mSharedObjects.push_back(dll);
					}
					else
					{
						FreeLibrary(dll);
						System::Log::GetInstance()->Error(
							string("Could not load [" + it->filename().string() +
							"] the LoadPlugin function was not found") );
					}
				}
				else
				{
					System::Log::GetInstance()->Error(
						string("Could not load ") + it->filename().string());
					cout << WSAGetLastError() << endl;
				}
			}
#else
			if(it->extension() == ".so")
			{
				System::Log::GetInstance()->Error
			}
#endif
		}

		for(auto it = mPlugins.begin(); it != mPlugins.end(); it++)
		{
			std::get<0>(*it)->OnEnable();
		}
	}
	//---------------------------------------------------------------------------------------
	void PluginManager::Free()
	{
		for(auto it = mPlugins.begin(); it != mPlugins.end(); it++)
		{
			std::get<0>(*it)->OnDisable();
		}

		for(auto it = mSharedObjects.begin(); it != mSharedObjects.end(); it++)
		{
#if defined(WIN32)
			FreeLibrary(*it);
#else
			dlclose(*it);
#endif
		}
	}
	//---------------------------------------------------------------------------------------
	void PluginManager::AddShard(Game::IWorld* world)
	{
		//world->CreateJava();

		for(auto it = mServerListeners.begin(); it != mServerListeners.end(); it++)
		{
				(*it)->OnNewShard(world);
		}
	}
	//---------------------------------------------------------------------------------------
	void PluginManager::Register(void* plugin, int event)
	{
		switch(event)
		{
			case SERVER: mServerListeners.push_back((Plugin*)plugin); break;
			case WORLD: mWorldListeners.push_back((Plugin*)plugin); break;
		}
	}
	//---------------------------------------------------------------------------------------
}
}
*/
