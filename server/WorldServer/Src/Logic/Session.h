#pragma once

#include <DAO/DAO.h>
#include <System/EventListener.h>
#include <Logic/Account.h>
#include <Crypt/Cipher.h>
#include <Network/Connection.h>
#include <Network/Packet.h>

#include <Game/Character.h>

#include <boost/asio.hpp>
#include <boost/tuple/tuple.hpp>
#include <bullet/btBulletCollisionCommon.h>

#include <deque>
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

			enum Queries
			{
				LOAD_USER = 0
			};

			Session(Network::Connection::pointer pConnection, World* pWorld, uint32_t pId);
			virtual ~Session();

			/**
			 * bad_weak_ptr if not done like this :(
			 * @return A pointer to the session
			 */
			pointer shared_from_this();
			/**
			 * Starts listening to the session
			 */
			void Start();
			/**
			 * Parse packets, run logic...
			 */
			void Update(uint32_t pElapsed);
			/**
			 * Set up the opcode handlers, must be called once
			 */
			static void Setup();
			/**
			 * Get the session's id
			 * @return The id
			 */
			unsigned int GetId();
			/**
			 * Write a packet to the session
			 * @param pPacket The packet to write
			 */
			void Write(Network::Packet& pPacket);

		protected:

			/// Handlers
				// General
			void HandlePing(Network::Packet& pPacket);
			void HandleBlackHole(Network::Packet& pPacket);
			void HandleUnkC26464A9(Network::Packet& pPacket);
			void HandleHackNotify(Network::Packet& pPacket);
			void HandleGameState(Network::Packet& pPacket);
			void HandleClientModules(Network::Packet& pPacket);
			void HandleClientError(Network::Packet& pPacket);
				// Authentication
			void HandleHandshake(Network::Packet& pPacket);
			void HandleRequestClose(Network::Packet& pPacket);
				// Service
			void HandleServiceRequest(Network::Packet& pPacket);
			void HandleServiceAck(Network::Packet& pPacket);
			void HandleTimeServerRequest(Network::Packet& pPacket);
			void HandleChatMessage(Network::Packet& pPacket);
				// Characters
			void HandleCharacterDelete(Network::Packet& pPacket);
			void HandleCharacterCreate(Network::Packet& pPacket);
			void HandleCharacterList(Network::Packet& pPacket);
			void HandleCharacterSelect(Network::Packet& pPacket);
			void HandleCharacterSomething(Network::Packet& pPacket);
			void HandleUnk874B000B(Network::Packet& pPacket);
				// TBD
			void HandleUnk34287945(Network::Packet& pPacket);
			void HandleUnk8C6422C1(Network::Packet& pPacket);
			void HandleUnkA4BCD6F2(Network::Packet& pPacket);
			void HandleUnk7DAA9F08(Network::Packet& pPacket);
			void HandleUnk3E7D74F5(Network::Packet& pPacket);
			void HandleUnk463B0D17(Network::Packet& pPacket);
			void HandleUnkB4BF82C3(Network::Packet& pPacket);
			void HandleUnk8A2B911C(Network::Packet& pPacket);
			void HandleUnk54846FBB(Network::Packet& pPacket);
			void HandleUnkCA2408CA(Network::Packet& pPacket);
			void HandleUnk74361BD6(Network::Packet& pPacket);
			void HandleUnk45F77B86(Network::Packet& pPacket);
			void HandleUnk9FF5CB09(Network::Packet& pPacket);
			void HandleUnk65662EE3(Network::Packet& pPacket);
			void HandleUnkE00561B1(Network::Packet& pPacket);
			void HandleUnkCA2CD23C(Network::Packet& pPacket);
			void HandleUnkE6779198(Network::Packet& pPacket);
			void HandleUnk6B5AE34F(Network::Packet& pPacket);
			void HandleUnk13831C74(Network::Packet& pPacket);
			void HandleUnk8EB28DE9(Network::Packet& pPacket);
			void HandleUnk41D98BE4(Network::Packet& pPacket);
			void HandleUnkF96DCDB0(Network::Packet& pPacket);
			/// End Handlers

			/// Database callbacks
			void HandleUserLoad();
			void HandleUserLoad(DAO::IDAO::Type pType, bool pSucceeded);
			/// End database callbacks

			/// Senders
				// General
			void SendIntroduceConnection();
			void SendClientInformation();
			void SendServiceResponse(uint32_t pId, const std::string& pData1, const std::string& pData2, const std::string& pSignature);
				/// Character
			void SendCharacterCreateResponse(uint16_t pContV, uint16_t pTranV, const std::string& pName, uint32_t pResponse);
			void SendCharacterList(uint16_t pContV, uint16_t pTranV);
			void AddCharacter(Game::Character& pChar, Network::Packet& pPacket);
			void SendCharacterSelect(uint16_t pContV, uint16_t pTranV);
			void SendCharacterCurrentMap(uint16_t pContV, uint16_t pTranV, const std::string& pMapName, const std::string& pMapId);
			void SendTravelStatus(uint16_t pContV, uint16_t pTranV, uint32_t status);
			void SendCharacterRegionSpecs(uint16_t pContV, uint16_t pTranV, const std::string& pMapName, const std::string& pMapId);
			void SendCharacterTeleport(const btVector3& pPosition, const btVector3& pRotation);
            void SendRejectCharacterSelection(uint16_t pContV, uint16_t pTranV, uint64_t guid, uint32_t error);
            void SendToCharacterSelect(uint16_t pContV, uint16_t pTranV);
            void SendCharacterDeleteStatus(uint16_t pContV, uint16_t pTranV, uint64_t guid, uint16_t unks, uint8_t unkb, uint32_t error);

				/// Service
			void SendTimeServerReply(uint16_t pContV, uint16_t pTranV);
			void SendChatMessage(const std::string& pFrom, const std::string& pChannel, const std::string& pMessage, unsigned int pType = 0x33);
				/// System
			void SendGauntletVersion();
			void SendScriptErrors(bool pSendErrors = true);
			void SendHackPackFromWorld();
			void SendGameSystemId();
			void SendTrackingServerInit();
			void Send34287945();
				/// Options
			void SendAwarenessRange(float pEnterAwarenessDistance = 9.0f, float pEscapeAwarenessDistance = 13.5f);
			/// End Senders

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);
			typedef  void(Session::*QueryCallback)();
			Network::Connection::pointer mConnection;

			World*							mWorld;

			std::list<Session::pointer>		mInRange;

			uint32_t mId;
			Logic::Account mAccount;
			std::list<Game::Character> mCharacters;

			// static handlers
			static std::unordered_map<uint32_t, CallBack> mHandlers;
			static std::unordered_map<uint32_t, QueryCallback> mQueryHandlers;
		};
	}
}