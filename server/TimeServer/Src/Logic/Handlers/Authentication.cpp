#include <Logic/Session.h>
#include <Logic/World.h>
#include <Network/Packet.h>
#include <Crypt/RSA.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandleHandshake()
		{
			mTimeConnection->Start();
		}
		//---------------------------------------------------------------------
	}
}