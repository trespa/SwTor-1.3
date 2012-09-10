#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandlePing(Network::Packet& pPacket)
		{
			Network::Packet packet(pPacket.Opcode, 0, 0, Opcode::SMSG_PING);
			packet << "";

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::HandleBlackHole(Network::Packet& pPacket)
		{
			std::ostringstream os;
			os << "Unknown opcode : 0x" << std::hex << pPacket.Opcode;
			System::PrintBinary((uint8_t*)pPacket.GetBuffer().data(), pPacket.GetBuffer().size(), os.str());
		}
		//---------------------------------------------------------------------
		void Session::HandleUnkC26464A9(Network::Packet& pPacket)
		{
            uint32_t count;
            std::list<uint8_t> bytelist;

            pPacket >> count;

            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }
			// Don't know what this is, not handling it doesn't change anything
			//System::PrintBinary((unsigned char*)pPacket.GetBuffer().data(), pPacket.GetBuffer().size(), "HandleUnkC26464A9");
		}
		//---------------------------------------------------------------------
		void Session::HandleHackNotify(Network::Packet& pPacket)
		{
			uint32_t count;
			std::list<uint8_t> bytelist;

			pPacket >> count;

			for (uint32_t i = 0; i < count; ++i)
			{
				uint8_t temp;
				pPacket >> temp;

				bytelist.push_back(temp);
			}
			// Don't know what this is, not handling it doesn't change anything
			//System::PrintBinary((unsigned char*)pPacket.GetBuffer().data(), pPacket.GetBuffer().size(), "HandleHackNotify");
		}
		//---------------------------------------------------------------------
		void Session::HandleClientError(Network::Packet& pPacket)
		{
			std::string error, callstack;
			pPacket >> error >> callstack;
			System::Log::Debug(error);
			System::Log::Debug(callstack);
		}
		//---------------------------------------------------------------------
		void Session::HandleUnk34287945(Network::Packet& pPacket)
		{
			uint32_t unk01;
			uint32_t unk02;
			uint32_t constant01;
			uint32_t constant02;

			pPacket >> unk01 >> constant01 >> constant02 >> unk02;
		}
		//---------------------------------------------------------------------
		void Session::HandleGameState(Network::Packet& pPacket)
		{
			std::string state;
			std::uint64_t padding;
			pPacket >> padding >> padding >> state;

			std::ostringstream os;
			os << "Client is in \"" << state << "\"";
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
		void Session::HandleClientModules(Network::Packet& pPacket)
		{
			SendGauntletVersion();
			SendScriptErrors();
			SendTrackingServerInit();
			SendGameSystemId();
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk8C6422C1(Network::Packet& pPacket)
		{
			uint32_t count;
            std::list<uint8_t> bytelist;

            pPacket >> count;

			for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }

            std::ostringstream os;
			os << "Packet 0x13831C74 content: list";
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkA4BCD6F2(Network::Packet& pPacket)
		{
			uint32_t unk;
            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0xA4BCD6F2 content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk7DAA9F08(Network::Packet& pPacket)
		{
			std::string unk;
            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0x7DAA9F08 content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk3E7D74F5(Network::Packet& pPacket)
		{
            uint32_t unkint;
			std::string unk1, unk2;

            pPacket >> unkint >> unk1 >> unk2;

            std::ostringstream os;
			os << "Packet 0x3E7D74F5 content: " << unkint << " | " << unk1 << " | " << unk2;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk463B0D17(Network::Packet& pPacket)
		{
            uint32_t unkint;
			std::string unk;

            pPacket >> unkint >> unk;

            std::ostringstream os;
			os << "Packet 0x463B0D17 content: " << unkint << " | " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkB4BF82C3(Network::Packet& pPacket)
		{
            uint32_t unkint;

            pPacket >> unkint;

            std::ostringstream os;
			os << "Packet 0xB4BF82C3 content: " << unkint;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk8A2B911C(Network::Packet& pPacket)
		{
            uint32_t unkint1, unkint2, count;
            std::string unk1, unk2, unk3;
            std::list<uint8_t> bytelist;

            pPacket >> unkint1 >> unk1 >> unkint2 >> unk2 >> unk3;

            pPacket >> count;

            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }

            std::ostringstream os;
			os << "Packet 0x8A2B911C content: " << unkint1  << " | " << unkint2 << " | " << unk1 << " | " << unk2 << " | " << unk3;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk54846FBB(Network::Packet& pPacket)
		{
            uint32_t unkint1, unkint2, unkint3, unkint4;
            std::string unk1, unk2, unk3;
            std::list<uint8_t> bytelist;

            pPacket >> unkint1 >> unk1 >> unkint2 >> unk2 >> unk3 >> unkint3 >> unkint4;

            std::ostringstream os;
			os << "Packet 0xB4BF82C3 content: " << unkint1  << " | " << unkint2 << " | " << unk1 << " | " << unk2 << " | " << unk3 << " | " << unkint3 << " | " << unkint4;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkCA2408CA(Network::Packet& pPacket)
		{
			uint32_t unk1, unk2, count;
            std::list<uint8_t> bytelist;

            pPacket >> unk1 >> unk2 >> count;

            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }

            std::ostringstream os;
			os << "Packet 0xCA2408CA content: " << unk1  << " | " << unk2;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk74361BD6(Network::Packet& pPacket)
		{
			uint32_t unk;
            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0x74361BD6 content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk45F77B86(Network::Packet& pPacket)
		{
			uint64_t unk;
            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0x45F77B86 content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk9FF5CB09(Network::Packet& pPacket)
		{
			uint64_t unk;
            std::string unk1;

            pPacket >> unk >> unk1;

            std::ostringstream os;
			os << "Packet 0x9FF5CB09 content: " << unk  << " | " << unk1;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk65662EE3(Network::Packet& pPacket)
		{
			uint64_t unk;
            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0x65662EE3 content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkE00561B1(Network::Packet& pPacket)
		{
			std::string unk1, unk2;
            pPacket >> unk1 >> unk2;

            std::ostringstream os;
			os << "Packet 0xE00561B1 content: " << unk1 << " | " << unk2;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkCA2CD23C(Network::Packet& pPacket)
		{
            uint8_t unk;
			uint64_t unk1, unk2, unk3;
            pPacket >> unk1 >> unk >> unk2 >> unk3;

            std::ostringstream os;
			os << "Packet 0xCA2CD23C content: " << unk << " | " << unk1 << " | " << unk2 << " | " << unk3;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkE6779198(Network::Packet& pPacket)
		{
            uint64_t unk1;
			std::string unk2;
            pPacket >> unk1 >> unk2;

            std::ostringstream os;
			os << "Packet 0xE6779198 content: " << unk1 << " | " << unk2;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk6B5AE34F(Network::Packet& pPacket)
		{
            std::string unk;

            pPacket >> unk;

            std::ostringstream os;
			os << "Packet 0x6B5AE34F content: " << unk;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk13831C74(Network::Packet& pPacket)
		{
            std::ostringstream os;
			os << "Packet 0x13831C74 content: empty";
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk8EB28DE9(Network::Packet& pPacket)
		{
			uint32_t count;
            std::list<uint8_t> bytelist;

            pPacket >> count;

            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }

            std::ostringstream os;
			os << "Packet 0x8EB28DE9 content: list";
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnk41D98BE4(Network::Packet& pPacket)
		{
			std::string unk1, unk2;
            pPacket >> unk1 >> unk2;

            std::ostringstream os;
			os << "Packet 0x41D98BE4 content: " << unk1 << " | " << unk2;
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
        void Session::HandleUnkF96DCDB0(Network::Packet& pPacket)
		{
			uint32_t count;
            std::list<uint8_t> bytelist;

            pPacket >> count;

            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t temp;
                pPacket >> temp;

                bytelist.push_back(temp);
            }

            std::ostringstream os;
			os << "Packet 0xF96DCDB0 content: list";
			System::Log::Debug(os.str());
		}
		//---------------------------------------------------------------------
	}
}