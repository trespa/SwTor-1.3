#pragma once

#include <Logic/Session.h>
#include <Network/Server.h>
#include <Network/Connection.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>

namespace Swtor
{
	namespace Logic
	{
		class World
			: public boost::enable_shared_from_this<World>, private boost::noncopyable
		{
		public:

			/**
			 * Instantiate the server
			 * @param pPort The port to start the server on
			 */
			World(unsigned short pPort);

			/**
			 * Drops a player from the server, must never be called !
			 * @param pSession The session to drop from the server and world
			 */
			void Remove(Session::pointer pSession);

			/**
			 * Get the database work queue, needed to load a DAO
			 * @return the database work queue
			 */
			System::DBWorkQueue* GetDatabaseWorkQueue();

			void OnConnection(Network::Connection::pointer pConnection);

			void OnUpdate(uint32_t pDelta);

		private:

			Network::Server							mServer;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;

			std::unique_ptr<System::DBWorkQueue>    mDBWorkQueue;

			uint16_t mId;
		};
	}
}