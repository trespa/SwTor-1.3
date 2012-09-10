#include <Logic/Session.h>
#include <Logic/World.h>
#include <Network/Packet.h>
#include <System/Log.h>
#include <System/Tools.h>

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
			mHandlers[Opcode::CMSG_REQUEST_CLOSE] = &Session::HandleRequestClose;
			mHandlers[Opcode::MSG_SIGNATURE] = &Session::HandleServiceAck;
			mHandlers[Opcode::CMSG_SERVICE_REQUEST] = &Session::HandleServiceRequest;
			mHandlers[Opcode::CMSG_TIME_SERVER_REQUEST] = &Session::HandleTimeServerRequest;

			mHandlers[Opcode::CMSG_ERROR_DEBUG] = &Session::HandleClientError;
			mHandlers[Opcode::CMSG_LIST_MODULES] = &Session::HandleClientModules;

			mHandlers[Opcode::CMSG_UNK_34287945] = &Session::HandleUnk34287945;
			mHandlers[Opcode::CMSG_WORLD_HACKNOTIFY] = &Session::HandleHackNotify;
			mHandlers[Opcode::CMSG_UNK_C26464A9] = &Session::HandleUnkC26464A9;
			mHandlers[Opcode::CMSG_GAME_STATE] = &Session::HandleGameState;

			mHandlers[Opcode::CMSG_CHARACTER_DELETE] = &Session::HandleCharacterDelete;
			mHandlers[Opcode::CMSG_CHARACTER_CREATE] = &Session::HandleCharacterCreate;
			mHandlers[Opcode::CMSG_CHARACTER_LIST] = &Session::HandleCharacterList;
			mHandlers[Opcode::CMSG_CHARACTER_SELECT] = &Session::HandleCharacterSelect;
			mHandlers[Opcode::CMSG_CHARACTER_SOMETHING] = &Session::HandleCharacterSomething;
			mHandlers[Opcode::CMSG_UNK_874B000B] = &Session::HandleUnk874B000B;

			mHandlers[Opcode::CMSG_UNK_8C6422C1] = &Session::HandleUnk8C6422C1;
			mHandlers[Opcode::CMSG_UNK_A4BCD6F2] = &Session::HandleUnkA4BCD6F2;
			mHandlers[Opcode::CMSG_UNK_7DAA9F08] = &Session::HandleUnk7DAA9F08;
			mHandlers[Opcode::CMSG_UNK_3E7D74F5] = &Session::HandleUnk3E7D74F5;
			mHandlers[Opcode::CMSG_UNK_463B0D17] = &Session::HandleUnk463B0D17;
			mHandlers[Opcode::CMSG_UNK_B4BF82C3] = &Session::HandleUnkB4BF82C3;
			mHandlers[Opcode::CMSG_UNK_8A2B911C] = &Session::HandleUnk8A2B911C;
			mHandlers[Opcode::CMSG_UNK_54846FBB] = &Session::HandleUnk54846FBB;
			mHandlers[Opcode::CMSG_UNK_CA2408CA] = &Session::HandleUnkCA2408CA;
			mHandlers[Opcode::CMSG_UNK_74361BD6] = &Session::HandleUnk74361BD6;
			mHandlers[Opcode::CMSG_UNK_45F77B86] = &Session::HandleUnk45F77B86;
			mHandlers[Opcode::CMSG_UNK_9FF5CB09] = &Session::HandleUnk9FF5CB09;
			mHandlers[Opcode::CMSG_UNK_65662EE3] = &Session::HandleUnk65662EE3;
			mHandlers[Opcode::CMSG_UNK_E00561B1] = &Session::HandleUnkE00561B1;
			mHandlers[Opcode::CMSG_UNK_CA2CD23C] = &Session::HandleUnkCA2CD23C;
			mHandlers[Opcode::CMSG_UNK_E6779198] = &Session::HandleUnkE6779198;
			mHandlers[Opcode::CMSG_UNK_6B5AE34F] = &Session::HandleUnk6B5AE34F;
			mHandlers[Opcode::CMSG_UNK_13831C74] = &Session::HandleUnk13831C74;
			mHandlers[Opcode::CMSG_UNK_8EB28DE9] = &Session::HandleUnk8EB28DE9;
			mHandlers[Opcode::CMSG_UNK_41D98BE4] = &Session::HandleUnk41D98BE4;
			mHandlers[Opcode::CMSG_UNK_F96DCDB0] = &Session::HandleUnkF96DCDB0;

			mQueryHandlers[LOAD_USER] = &Session::HandleUserLoad;
		}
		//---------------------------------------------------------------------
		Session::Session(Network::Connection::pointer pConnection, World* pWorld, uint32_t pId)
			: mConnection(pConnection), mWorld(pWorld), mId(pId)
		{
			System::Log::Debug("New connection !");
		}
		//---------------------------------------------------------------------
		Session::~Session()
		{
			mConnection->Close();
			System::Log::Debug("User left !");
		}
		//---------------------------------------------------------------------
		Session::pointer Session::shared_from_this()
		{
			return boost::dynamic_pointer_cast<Session>(EventListener::shared_from_this());
		}
		//---------------------------------------------------------------------
		void Session::Start()
		{
			Network::Packet packet(0x11, 0x0, 0x0, Opcode::SMSG_HANDSHAKE);

			mConnection->Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::Write(Network::Packet& pPacket)
		{
			mConnection->Write(pPacket);
		}
		//---------------------------------------------------------------------
		void Session::Update(uint32_t pElapsed)
		{
			if (mConnection->IsOffline())
			{
				mWorld->Remove(shared_from_this());
				return;
			}

			mLock.lock();

			while (!mEvents.empty())
			{
				System::Event::pointer e = mEvents.front();
				mEvents.pop();

				try
				{
					(this->*mQueryHandlers.at(e->userData))();
				}
				catch(...)
				{
				}
			}
			mLock.unlock();

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
					    default:
						    mConnection->Close();
						    break;
					}
				}
				catch (std::exception& e)
				{
					System::Log::Debug(e.what());
					HandleBlackHole(data);
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