#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>

int main()
{
	try
	{
		auto TimeServer = boost::make_shared<Swtor::Logic::World>(20080);
	}
	catch (std::exception& e)
	{
		Swtor::System::Log::GetInstance()->Error(e.what());
	}

	system("pause");
	return 0;
}