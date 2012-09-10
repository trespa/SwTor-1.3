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
		void Session::SendChatMessage(const std::string& pFrom, const std::string& pChannel, const std::string& pMessage, unsigned int pType)
		{
			Network::Packet packet(Opcode::SMSG_RECV_CHAT_MESSAGE, (uint16_t)(mId & 0x0000FFFF), (uint16_t)(mId & 0xFFFF0000));
			packet << pFrom << pChannel << pType << pMessage;

			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}