#include <Logic/Session.h>
#include <Logic/World.h>
#include <Network/Packet.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <fstream>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		std::unordered_map<uint32_t, Session::CallBack> Session::mHandlers;
		//---------------------------------------------------------------------
		void Session::Setup()
		{
			mHandlers[Opcode::MSG_REQUEST_SIGNATURE] = &Session::HandleServiceAck;
			mHandlers[Opcode::CMSG_REQUEST_INTRODUCE_CONNECTION] = &Session::HandleRequestIntroduceConnection;
			mHandlers[Opcode::CMSG_REQUEST_CLOSE] = &Session::HandleRequestClose;
		}
		//---------------------------------------------------------------------
		Session::Session(Network::Connection::pointer pConnection, World* pWorld, uint16_t pId)
			: mConnection(pConnection), mWorld(pWorld), mId(pId)
		{
			std::ostringstream os;
			os << "New connection !";
			System::Log::GetInstance()->Debug(os.str());
		}
		//---------------------------------------------------------------------
		Session::~Session()
		{
			mConnection->Close();

			std::ostringstream os;
			os << "User " << mAccount.User << " left";
			System::Log::GetInstance()->Debug(os.str());
		}
		//---------------------------------------------------------------------
		void Session::Start()
		{
			// Send handshake
			Network::Packet packet(0x11, 0x8, 0x0, Opcode::SMSG_HANDSHAKE);
			packet << (uint64_t)0x14AA63E353DBF459;

			mConnection->Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::Update()
		{
			if (mConnection->IsOffline())
			{
				mWorld->Remove(shared_from_this());
				return;
			}

			while (mConnection->HasPacket())
			{
				Network::Packet data = mConnection->PopPacket();

				try
				{
					switch (data.Type)
					{
					    case Opcode::CMSG_PACKET:
						    (this->*mHandlers.at(data.Opcode))(data);
						    break;
					    case Opcode::CMSG_PING:
						    HandlePing(data);
						    break;
					    case Opcode::CMSG_HANDSHAKE:
						    HandleHandshake(data);
						    break;
					}
				}
				catch (std::exception& e)
				{
					std::ostringstream os;
					os << "Ran into an unknown packet Opcode : " << std::hex << data.Opcode;
					os << std::endl << e.what();
					System::Log::GetInstance()->Error(os.str());
				}
			}
		}
		//---------------------------------------------------------------------
		unsigned int Session::GetId()
		{
			return mAccount.Id;
		}
		//---------------------------------------------------------------------
	}
}