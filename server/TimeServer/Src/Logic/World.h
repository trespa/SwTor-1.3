#pragma once

#include <Logic/Session.h>
#include <Network/TimeServer.h>
#include <Network/TimeConnection.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>

namespace Swtor
{
	namespace Logic
	{
		class World
			: public System::EventListener, private boost::noncopyable
		{
		public:

			/**
			 * Instantiate the TimeServer
			 * @param pPort The port to start the TimeServer on
			 */
			World(unsigned short pPort);

			/**
			 * Drops a player from the TimeServer, must never be called !
			 * @param pSession The session to drop from the TimeServer and world
			 */
			void Remove(Session::pointer pSession);

			/**
			 * Get the database work queue, needed to load a DAO
			 * @return the database work queue
			 */
			System::DBWorkQueue* GetDatabaseWorkQueue();

			void OnTimeConnection(Network::TimeConnection::pointer pTimeConnection);

			void OnUpdate(uint32_t pDelta);

			/**
			 * Event callback, don't call it explicitly !!!!
			 */
			virtual void OnEvent(std::shared_ptr<System::Event> pEvent);

		private:

			Network::TimeServer							mTimeServer;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;

			std::unique_ptr<System::DBWorkQueue>    mDBWorkQueue;

			uint16_t mId;
		};
	}
}