#include <Logic/World.h>
#include <System/Log.h>
#include <Crypt/Cipher.h>
#include <System/Tools.h>

int main()
{
	try
	{
		auto server = boost::make_shared<Swtor::Logic::World>(7979);
	}
	catch (std::exception& e)
	{
		Swtor::System::Log::GetInstance()->Error(e.what());
	}

	system("pause");
	return 0;
}