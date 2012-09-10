#pragma once

#include <System/EventListener.h>
#include <Network/Packet.h>
#include <Network/TimeConnection.h>
#include <boost/asio.hpp>
#include <boost/tuple/tuple.hpp>

#include <unordered_map>

namespace Swtor
{
	namespace Logic
	{
		// Forward declaration
		class World;
		/**
		 * @class Session
		 * @brief Handles a single client as a session
		 */
		class Session :
			public System::EventListener, private boost::noncopyable
		{
		public:

			typedef boost::shared_ptr<Session> pointer;

			/// SQL query opcodes
			enum Queries
			{
				LOAD_USER = 0
			};

			Session(Network::TimeConnection::pointer pTimeConnection, World* pWorld, uint16_t pId);
			virtual ~Session();

			/**
			 * bad_weak_ptr if not done like this :(
			 * @return A pointer to the session
			 */
			pointer shared_from_this();

			/**
			 * Once instantiated, run some stuff
			 */
			void Start();

			/**
			 * Parse packets, run logic...
			 */
			void Update();

			/**
			 * Set up the opcode handlers, must be called once
			 */
			static void Setup();

			unsigned int GetId();

		protected:

			/// Handlers
			void HandleHandshake();
			/// End database callbacks

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);
			typedef  void(Session::*QueryCallback)();
			Network::TimeConnection::pointer	mTimeConnection;

			bool							mGotHandshake;
			World*							mWorld;
			uint16_t						mId;
			std::string						mShard;

			char							mBulk[20];

			// static handlers
			static std::unordered_map<uint32_t, CallBack> mHandlers;
			static std::unordered_map<uint32_t, QueryCallback> mQueryHandlers;
		};
	}
}