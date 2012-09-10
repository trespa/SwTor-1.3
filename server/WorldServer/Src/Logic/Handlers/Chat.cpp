#include <Logic/Session.h>
#include <Logic/World.h>
#include <DAO/Account.h>
#include <Crypt/RSA.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandleChatMessage(Network::Packet& pPacket)
		{
			std::string channel;
			std::string message;
			pPacket >> channel >> message;

			SendChatMessage(mAccount.User, channel, message);
		}
		//---------------------------------------------------------------------
	}
}