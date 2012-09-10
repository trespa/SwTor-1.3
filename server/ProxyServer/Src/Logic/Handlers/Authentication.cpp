#include <Logic/Session.h>
#include <Logic/World.h>
#include <Network/Packet.h>
#include <DAO/Account.h>
#include <Crypt/RSA.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		static std::string GenRandom()
		{
			static const char alphanum[] = 
				"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

			std::string ret;
			ret.resize(15);

			for (int i = 0; i < 15; ++i) {
				ret[i] = alphanum[rand() % sizeof(alphanum)];
			}

			return ret;
		}
		//---------------------------------------------------------------------
		void Session::HandleHandshake(Network::Packet& pData)
		{
			std::string hash;
			std::string rsaData;

			for(auto i = 4; i < pData.GetBuffer().size(); i += 2)
			{
				int c = 0x0;
				sscanf(&pData.GetBuffer()[i], "%02X", &c);
				rsaData.push_back(c);
			}
			rsaData = Crypt::RSA::Decrypt(rsaData);
			pData.Initialize(rsaData);
			pData >> mAccount.SessionId >> hash;

			mAccount.ServerId = GenRandom();

			std::string salsaEnc, salsaDec, salsaEncIV, salsaDecIV;
			salsaEnc = pData.GetBuffer().substr(0,32);
			salsaDec = pData.GetBuffer().substr(32,32);
			salsaEncIV = pData.GetBuffer().substr(64,8);
			salsaDecIV = pData.GetBuffer().substr(72,8);

			auto loader = DAO::Load(mAccount);
			loader->OnEvent.connect(boost::bind(&Session::HandleUserLoad, shared_from_this(), _1, _2));
			mWorld->GetDatabaseWorkQueue()->Push(loader);

			mConnection->SetCipher(new Crypt::Cipher(salsaEnc, salsaDec, salsaEncIV, salsaDecIV));
		}
		//---------------------------------------------------------------------
		void Session::HandleServiceAck(Network::Packet& packet)
		{
			uint64_t replyId;
			packet >> mShard >> replyId;

			std::ostringstream os;
			os << "User " << mAccount.User << " wants to connect to shard " << mShard;
			System::Log::GetInstance()->Debug(os.str());

			Network::Packet pack(Opcode::MSG_SIGNATURE, 0xFFFF, 0xFFFF);
			pack << (uint16_t)0x04 << mShard << "afc1bb5a" << "loginserver" << replyId;

			mConnection->Write(pack);
		}
		//---------------------------------------------------------------------
		void Session::HandleRequestClose(Network::Packet& packet)
		{
			mConnection->Close();
		}
		//---------------------------------------------------------------------
		void Session::HandlePing(Network::Packet& packet)
		{
			Network::Packet oPacket(packet.Opcode, 0, 0, Opcode::SMSG_PING);
			oPacket << "";

			mConnection->Write(oPacket);
		}
		//---------------------------------------------------------------------
		void Session::HandleRequestIntroduceConnection(Network::Packet& packet)
		{
			Network::Packet oPacket(Opcode::SMSG_REQUEST_INTRODUCE_CONNECTION, 0x04, 0x00, 0x00);
			if(mShard == "testshard" || mShard == "devshard")
				oPacket << "localhost:20061" << mAccount.ServerId;
			else
				oPacket << "emulatornexus.com:20061" << mAccount.ServerId;
			mConnection->Write(oPacket);
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