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
		void Session::SendAwarenessRange(float pEnterAwarenessDistance /* = 9.f */, float pEscapeAwarenessDistance /* = 13.5f */)
		{
			Network::Packet packet(Opcode::SMSG_AWARENESS_RANGE, (uint16_t)(mId & 0x0000FFFF), (uint16_t)(mId & 0xFFFF0000));
			packet << pEnterAwarenessDistance << pEscapeAwarenessDistance;

			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}