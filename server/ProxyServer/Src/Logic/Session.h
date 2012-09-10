#pragma once

#include <DAO/DAO.h>
#include <Entity/Account.h>
#include <Network/Packet.h>
#include <Network/Connection.h>
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
		class Session : public boost::enable_shared_from_this<Session>, private boost::noncopyable
		{
		public:

			typedef boost::shared_ptr<Session> pointer;

			Session(Network::Connection::pointer pConnection, World* pWorld, uint16_t pId);
			virtual ~Session();

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
			void HandleHandshake(Network::Packet& packet);
			void HandleServiceAck(Network::Packet& packet);
			void HandleRequestIntroduceConnection(Network::Packet& packet);
			void HandlePing(Network::Packet& packet);
			void HandleRequestClose(Network::Packet& packet);
			/// End Handlers
			/// Database callbacks
			void HandleUserLoad(DAO::IDAO::Type pType, bool pSucceeded);
			/// End database callbacks

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);
			typedef  void(Session::*QueryCallback)();
			Network::Connection::pointer	mConnection;

			World*							mWorld;
			uint16_t						mId;
			std::string						mShard;

			Entity::Account mAccount;

			// static handlers
			static std::unordered_map<uint32_t, CallBack> mHandlers;
		};
	}
}