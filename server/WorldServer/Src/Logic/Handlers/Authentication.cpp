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
		void Session::HandleHandshake(Network::Packet& pPacket)
		{
			std::string token;
			std::string what;
			std::string rsaData;

			for(size_t i = 4; i < pPacket.GetBuffer().size(); i += 2)
			{
				int c = 0x0;
				sscanf(&pPacket.GetBuffer()[i], "%02X", &c);
				rsaData.push_back(c);
			}
			rsaData = Crypt::RSA::Decrypt(rsaData);
			pPacket.Initialize(rsaData);
			pPacket >> mAccount.User >> what;

			std::string salsaEnc, salsaDec, salsaEncIV, salsaDecIV;
			salsaEnc = pPacket.GetBuffer().substr(0,32);
			salsaDec = pPacket.GetBuffer().substr(32,32);
			salsaEncIV = pPacket.GetBuffer().substr(64,8);
			salsaDecIV = pPacket.GetBuffer().substr(72,8);

			auto loader = DAO::Load(mAccount);
			loader->OnEvent.connect(boost::bind(&Session::HandleUserLoad, shared_from_this(), _1, _2));
			mWorld->GetDatabaseWorkQueue()->Push(loader);

			mConnection->SetCipher(new Crypt::Cipher(salsaEnc, salsaDec, salsaEncIV, salsaDecIV));

			Network::Packet packet(Opcode::MSG_REQUEST_SIGNATURE, 0xFFFF, 0xFFFF);
			packet << "OmegaServerProxyObjectName" << (uint32_t)0x1e46d << (uint64_t)0;

			mConnection->Write(packet);
			//mConnection->Start();
		}
		//---------------------------------------------------------------------
		void Session::HandleRequestClose(Network::Packet& pPacket)
		{
			//mConnection->Close();
		}
		//---------------------------------------------------------------------
		void Session::HandleUserLoad()
		{
			if(mAccount.Id != 0)
			{
			}
			else
			{
				mConnection->Close();
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleUserLoad(DAO::IDAO::Type pType, bool pSucceeded)
		{
			if(mAccount.Id != 0)
			{
				std::ostringstream os;
				os << "User " << mAccount.User << " successfully logged in !";
				System::Log::GetInstance()->Debug(os.str());
				mConnection->Start();
			}
			else
			{
				std::ostringstream os;
				os << "Request to enter from " << mAccount.SessionId << " failed";
				System::Log::GetInstance()->Debug(os.str());
				mConnection->Close();
			}
		}
		//---------------------------------------------------------------------
	}
}