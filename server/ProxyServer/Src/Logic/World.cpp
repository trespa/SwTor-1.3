#include <Logic/World.h>
#include <System/Log.h>

using boost::asio::ip::tcp;

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		World::World(unsigned short pPort)
			:mId(0), mServer(pPort)
		{
			System::Log::Create("ProxyServer.log");
			System::Log::GetInstance()->Print("               Star Wars : The Old Republic         ");
			System::Log::GetInstance()->Print("Memory model : " + std::to_string((unsigned long long)sizeof(void*) * 8) + " bits				   ");

			Session::Setup();

			mServer.OnConnection.connect(boost::bind(&World::OnConnection, this, _1));
			mServer.OnUpdate.connect(boost::bind(&World::OnUpdate, this, _1));

			mDBWorkQueue.reset(new System::DBWorkQueue("sso", 1));

			mServer.Start();
		}
		//---------------------------------------------------------------------
		void World::OnConnection(Network::Connection::pointer pConnection)
		{
			Session::pointer session = boost::make_shared<Session>(pConnection, this, ++mId);

			mGuard.lock();
			mSessions.push_back(session);
			mGuard.unlock();

			session->Start();
		}
		//---------------------------------------------------------------------
		void World::OnUpdate(uint32_t pDelta)
		{
			mGuard.lock();
			auto sessionCopy(mSessions);
			mGuard.unlock();

			// Work with authenticating sessions
			std::for_each(sessionCopy.begin(), sessionCopy.end(),
				[this](Session::pointer pSession)
			{
				// Update must be synchronous
				pSession->Update();
			});
		}
		//---------------------------------------------------------------------
		void World::Remove(Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
			{
				mSessions.erase(itor);
			}
		}
		//---------------------------------------------------------------------
		System::DBWorkQueue* World::GetDatabaseWorkQueue()
		{
			return mDBWorkQueue.get();
		}
		//---------------------------------------------------------------------
	}
}