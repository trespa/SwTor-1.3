#include <Logic/World.h>
#include <System/Log.h>
#include <time.h>

using boost::asio::ip::tcp;

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		World::World(unsigned short pPort)
			:mId(0), mTimeServer(pPort)
		{
			System::Log::Create("TimeTimeServer.log");
			System::Log::GetInstance()->Print("               Star Wars : The Old Republic         ");
			System::Log::GetInstance()->Print("Memory model : " + std::to_string((unsigned long long)sizeof(void*) * 8) + " bits				   ");

			Session::Setup();

			mTimeServer.OnTimeConnection.connect(boost::bind(&World::OnTimeConnection, this, _1));
			mTimeServer.OnUpdate.connect(boost::bind(&World::OnUpdate, this, _1));

			mTimeServer.Start();
		}
		//---------------------------------------------------------------------
		void World::OnTimeConnection(Network::TimeConnection::pointer pTimeConnection)
		{
			Session::pointer session = boost::make_shared<Session>(pTimeConnection, this, ++mId);

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
		void World::OnEvent(std::shared_ptr<System::Event> pEvent)
		{
		}
		//---------------------------------------------------------------------
	}
}