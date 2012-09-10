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
		std::unordered_map<uint32_t, Session::QueryCallback> Session::mQueryHandlers;
		//---------------------------------------------------------------------
		void Session::Setup()
		{
		}
		//---------------------------------------------------------------------
		Session::Session(Network::TimeConnection::pointer pTimeConnection, World* pWorld, uint16_t pId)
			: mTimeConnection(pTimeConnection), mWorld(pWorld), mId(pId)
		{
			std::ostringstream os;
			os << "New TimeConnection from : " << mTimeConnection->GetSocket().remote_endpoint().address().to_string();
			System::Log::GetInstance()->Debug(os.str());
		}
		//---------------------------------------------------------------------
		Session::~Session()
		{
			mTimeConnection->Close();

			std::ostringstream os;
			os << "User disconnected !";
			System::Log::GetInstance()->Debug(os.str());
		}
		//---------------------------------------------------------------------
		Session::pointer Session::shared_from_this()
		{
			return boost::dynamic_pointer_cast<Session>(EventListener::shared_from_this());
		}
		//---------------------------------------------------------------------
		void Session::Start()
		{
			boost::asio::async_read(mTimeConnection->GetSocket(), boost::asio::buffer(mBulk), boost::asio::transfer_exactly(20),
				boost::bind(&Session::HandleHandshake, shared_from_this()));
		}
		//---------------------------------------------------------------------
		void Session::Update()
		{
			if(mTimeConnection->IsOffline())
			{
				mWorld->Remove(shared_from_this());
				return;
			}

			while(mTimeConnection->HasPacket())
			{
				Network::Packet data = mTimeConnection->PopPacket();

				if (data.GetBuffer().size() >= 20)
					continue;

				// Get system time
				time_t sysTime;
				sysTime = time(NULL);

				// Convert it to FILETIME
				int64_t fileTime;
				fileTime = ((int64_t)sysTime * (int64_t)10000000) + 116444736000000000;

				// Get the time sent from the client
				uint8_t pLength;
				uint32_t Unk01, Unk02;
				uint64_t Unk03, Unk04;
				data >> pLength >> Unk01 >> Unk02;

				// Do some math
				Unk03 = *(uint64_t*)&fileTime / 0x2710;
				Unk04 = *(uint64_t*)&fileTime / 0x2710 >> 32;

				// Construct our packet
				Network::Packet TimePacket;
				TimePacket << (uint8_t)0x10 << Unk01 << Unk02 << (uint32_t)Unk03 << (uint32_t)Unk04;

				mTimeConnection->Write(TimePacket);
			}
		}
		//---------------------------------------------------------------------
		unsigned int Session::GetId()
		{
			return 0;
		}
		//---------------------------------------------------------------------
	}
}