#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandleServiceRequest(Network::Packet& pPacket)
		{
			std::string serverType;
			std::string serviceName;
			std::string unk01, unk02;
			std::string serviceObjectName;
			std::string padding;
			std::string hash;

			pPacket >> serverType >> serviceName >> unk01 >> unk02 >> serviceObjectName >> padding >> hash;

			uint32_t responseid = 0;
			std::string sig = "";
			std::string data1 = "";

			if(serviceName == "timesource")
			{
				responseid = 0x010006;
				data1 = "timesource";
				sig = "462a9d1f";
			}
			else if(serviceName == "biomon")
			{
				responseid = 0x02505e;
				data1 = "sp1u796[biomonserver:biomon]yamashi.biomon";
				sig = "389fc8f0:9adcb7e6";
			}
			else if(serviceName == "worldserver")
			{
				responseid = 0x035059;
				data1 = "sp2u796[WorldServer:worldserver]yamashi.worldserver";
				sig = "51e518d9:92367cb3:29f2db17";
			}
			else if(serviceName == "gamesystemsserver")
			{
				responseid = 0x05505a;
				data1 = "sp3u796[GameSystemsServer:gamesystemsserver]yamashi.gamesystemsserver";
				sig = "450a2825";
			}
			else if(serviceName == "chatgateway")
			{
				responseid = 0x06505c;
				data1 = "sp4u796[ChatGateway:chatgateway]yamashi.chatgateway";
				sig = "900005df";
			}
			else if(serviceName == "auctionserver")
			{
				responseid = 0x07505b;
				data1 = "sp5u796[AuctionServer:auctionserver]yamashi.auctionserver";
				sig = "9ce839f7";
			}
			else if(serviceName == "mailserver")
			{
				responseid = 0x085058;
				data1 = "sp6u796[Mail:mailserver]yamashi.mailserver";
				sig = "9759aa23";
			}
			else if(serviceName == "trackingserver")
			{
				responseid = 0x09505d;
				data1 = "sp7u796[TrackingServer:trackingserver]yamashi.trackingserver";
				sig = "c5b320c1:8cebf93e";
			}
			else if(serviceName == "areaserver")
			{
				Network::Packet packet(Opcode::MSG_REQUEST_SIGNATURE, 0xFFFF, 0xFFFF);
				packet << "omegaareaobject" << uint64_t(0x858E) << uint32_t(0);

				Write(packet);
				return;
			}
			else
			{
				std::ostringstream os;
				os << "Client requests : " << serviceName << "\nFrom : " << serverType << "\nRequires object : " << serviceObjectName << "\nHash : " << hash;
				System::Log::Debug(os.str());

				return;
			}

			SendServiceResponse(responseid, data1, "userentrypoint6", sig);
		}
		//---------------------------------------------------------------------
		void Session::HandleServiceAck(Network::Packet& pPacket)
		{
			uint16_t serviceId;
			std::string serviceObjectName;
			std::string hash;
			std::string origin;
			uint64_t timestamp;

			pPacket >> serviceId >> serviceObjectName >> hash >> origin >> timestamp;

			if(serviceObjectName == "OmegaServerProxyObjectName")
			{
				SendIntroduceConnection();
				SendClientInformation();
			}
			else if(serviceObjectName == "omegaareaobject")
			{
				uint32_t responseid = 0x043507;
				std::string data1 = "sp8u796[AreaServer-ord_main-4611686019802843831-1-:areaserver]yamashi.areaserver";
				std::string sig = "91ac5777:62060b0:29f2db17";
				SendServiceResponse(responseid, data1, "userentrypoint6", sig);
			}
			else
			{
				std::ostringstream os;
				os << "Client ack service[" << serviceId << "] : " << serviceObjectName << "\nFrom : " << origin << "\nHash : " << hash;
				System::Log::Debug(os.str());
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleTimeServerRequest(Network::Packet& pPacket)
		{
			std::ostringstream os;
			os << "TimeServer Request";
			System::Log::Debug(os.str());

            SendTimeServerReply(pPacket.TransportV, pPacket.ContentV);
		}
		//---------------------------------------------------------------------
	}
}