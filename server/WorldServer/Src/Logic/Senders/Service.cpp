#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendServiceResponse(uint32_t pId, const std::string& pData1, const std::string& pData2, const std::string& pSignature)
		{
			Network::Packet packet(Opcode::SMSG_SIGNATURE_RESPONSE, 0xFFFF, 0xFFFF, 0x00);
			packet << (uint32_t)pId << pData1 << pData2 << pSignature;
			packet << (uint64_t)0 << "" << "" << (uint64_t)0;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendTimeServerReply(uint16_t contV, uint16_t transV)
		{
			Network::Packet packet(Opcode::SMSG_TIME_SERVER_REPLY, contV, transV);
			// TODO: Change localhost with actual timeserver address
			//packet << "timeserver.emulatornexus.com" << (uint32_t)20080 << (uint32_t)0x14 << (uint64_t)0x00 << (uint64_t)0x00<< (uint32_t)0x00;
            packet << "localhost" << (uint32_t)20080 << (uint32_t)0x14 << (uint64_t)0x00 << (uint64_t)0x00<< (uint32_t)0x00;
			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}