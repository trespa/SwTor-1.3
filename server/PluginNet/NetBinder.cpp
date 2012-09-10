// This is the main DLL file.

#include "NetBinder.h"
#include <iostream>
#include <list>
#include "..\Script\Src\Script\Plugin.h"
#include "..\Script\Src\Script\IPluginManager.h"

#if defined WIN32

#pragma managed
#include <gcroot.h>

ref class Binder
{
public:
	Binder(std::string path)
	{
		try
		{
			System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom(gcnew String(path.c_str()));
			type = assembly->GetType("Class1");
			obj = assembly->CreateInstance(type->FullName);
		}
		catch(System::Exception^ e)
		{
			Console::WriteLine("{0}",e);
		}
	}

	void OnNewShard(Object^ world)
	{
		type->GetMethod("OnNewShard")->Invoke(obj, gcnew cli::array<Object^>(1){world});
	}

	System::Object^ obj;
	Type^ type;
};

ref class SOScriptPimpl
{
public:
	SOScriptPimpl()
	{
		try
		{
			mPlugins = gcnew System::Collections::ArrayList;
			mWorldHolder = gcnew System::Collections::Hashtable;
			assembly = System::Reflection::Assembly::LoadFrom("SOScriptManaged.dll");
		}
		catch(System::Exception^ e)
		{
			Console::WriteLine("{0}",e);
		}
	}

	void OnEnable()
	{
		mPlugins->Add(gcnew Binder("Script/SampleManaged.mp"));
	}

	void OnNewShard(Swtor::Game::IWorld* world)
	{
		try
		{
			Type^ type = assembly->GetType("Swtor.Game.World");
			Object^ obj = assembly->CreateInstance(type->FullName);
			type->GetMethod("SetPointer")->Invoke(obj,gcnew cli::array<Object^>(1){System::Int64(world)});

			mWorldHolder->Add(System::Int64(world), obj);

			System::Collections::IEnumerator^ o = mPlugins->GetEnumerator();
			while(o->MoveNext())
			{
				((Binder^)(o->Current))->OnNewShard(obj);
			}
		}
		catch (System::Exception^ e)
		{
			System::Console::WriteLine("{0}", e->ToString());
		}
	}

	System::Collections::ArrayList^ mPlugins;
	System::Reflection::Assembly^ assembly;
	System::Collections::Hashtable^ mWorldHolder;
};

#endif

class __declspec(dllexport) DotNetBinder : public Swtor::Script::Plugin
{
public:

	DotNetBinder(Swtor::Script::IPluginManager* pPluginManager)
		:mPluginManager(pPluginManager)
	{
		mPimpl = gcnew SOScriptPimpl();
	}

	__declspec(nothrow) void OnEnable()
	{
		mPluginManager->Register((void*)this, Swtor::Script::IPluginManager::SERVER);
		mPluginManager->Register((void*)this, Swtor::Script::IPluginManager::WORLD);

		mPimpl->OnEnable();
	}
	__declspec(nothrow) void OnDisable(){}
	__declspec(nothrow) void OnNewShard(Swtor::Game::IWorld* world)
	{
		mPimpl->OnNewShard(world);
	}

private:

	gcroot<SOScriptPimpl^> mPimpl;
	Swtor::Script::IPluginManager* mPluginManager;
};

extern "C"
{
	__declspec(dllexport) Swtor::Script::Plugin* __stdcall LoadPlugin(Swtor::Script::IPluginManager* pPluginManager)
	{
		return new DotNetBinder(pPluginManager);
	}
};