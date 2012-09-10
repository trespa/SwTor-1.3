#include <Logic/Session.h>
#include <Logic/World.h>
#include <Game/Character.h>
#include <System/Tools.h>
#include <System/Log.h>

namespace Swtor
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::AddCharacter(Game::Character& pChar, Network::Packet& pPacket)
		{
			pPacket << pChar.mId;
			pPacket << pChar.unkFlags;

			if (pChar.unkFlags & 0x80)
				pPacket << pChar.UnkLong1;

			if (pChar.unkFlags & 0x40)
				pPacket << pChar.UnkLong2;

			if (pChar.unkFlags & 0x20)
			{
				pPacket << pChar.UnkLong3;
				pPacket << pChar.UnkLong4;
			}

			if (pChar.unkFlags & 0x10)
			{
				pPacket << pChar.unkVal;

				pPacket << (uint32_t)pChar.unkLongs.size();

				for (auto itr = pChar.unkLongs.begin(); itr != pChar.unkLongs.end(); ++itr)
					pPacket << *itr;
			}

			if (pChar.unkFlags & 0x08)
			{
				pPacket << pChar.unkShort;
				pPacket << pChar.unkByte;

				pPacket << (uint32_t)pChar.unkBytes.size();

				for (auto itr = pChar.unkBytes.begin(); itr != pChar.unkBytes.end(); ++itr)
					pPacket << *itr;
			}
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterCreateResponse(uint16_t pContV, uint16_t pTranV, const std::string& pName, uint32_t pResponse)
		{
			Network::Packet packet(Opcode::SMSG_CHARACTER_REJECT_NEW, pContV, pTranV);
			packet << pName << pResponse;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterList(uint16_t pContV, uint16_t pTranV)
		{
			/*
			Character List Structure (Probably)

			- CharacterCount
			+ Characters
				- NodeID
				- Flag
				(Flag & 0x80)
					- ClassID
				(Flag & 0x40)
					- TemplateID
				(Flag & 0x20)
					- Parent NodeID
				(Flag & 0x10)
					+ UnkStruct
				(Flag & 0x08)
					+ Character Fields
						- Fields Version
						- Fields Format
						+ Fields Payload
							- Unk Field Count
							- Actual Field Count 
							+ Fields
								- Field ID
								- Field Type
								- Field Data (depending on type)
			+ Gloomed Classes
			+ UnkData (probably EffEvent/Legacy related)
			- UserData (XML Format)
			- Int64 [0x00]
			*/


			std::string xml = "";
			xml += "<status><userdata>";
			xml += "<entitlement id=\"7\"    uniqueId=\"19669425\"    date_created=\"1324371113909\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"Subcriber Shard Access\" gameInfo=\"\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "<entitlement id=\"30\"    uniqueId=\"539043\"    date_created=\"1311840392836\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"Early Game Access\" gameInfo=\"\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "<entitlement id=\"39\"    uniqueId=\"15130593\"    date_created=\"1323871237000\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"Head Start\" gameInfo=\"Created by Head Start Package\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "<entitlement id=\"2013\"    uniqueId=\"19669424\"    date_created=\"1324371113907\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"SWTOR_COLLECTORS_RETAIL\" gameInfo=\"{&quot;transactionalEmail&quot;: {&quot;templatePrefix&quot;:&quot;PurchaseConfirmation.CR&quot;}}\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "<entitlement id=\"40\"    uniqueId=\"22765385\"    date_created=\"1324593971139\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"Security Key Associated\" gameInfo=\"\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "<entitlement id=\"71\"    uniqueId=\"29277571\"    date_created=\"1327348302784\"    date_consumed =\"\"    ";
			xml += "date_started=\"\" description=\"Early Founder\" gameInfo=\"\" shard_name=\"he1012\" key=\"\" type=\"G\"/>";

			xml += "</userdata></status>";

			Network::Packet packet(Opcode::SMSG_CHARACTER_LIST, pContV, pTranV);

			packet << (uint32_t)mCharacters.size();

			for (auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
				AddCharacter(*itor, packet);

			/*packet << (uint32_t)mLastChars.size();

			for (auto itor = mLastChars.begin(); itor != mLastChars.end(); ++itor)
				AddCharacter(*itor, packet);*/

			uint8_t data[] = 
			{
				0x6E, 0xA2, 0x9E, 0x22, 0x3A, 0x01, 0x00, 0x40, 0xAA, 0xE1, 0x3A, 0x4E, 0x3A, 0x35, 0x00, 0x00,
                0x40, 0xC9, 0x4D, 0x48, 0xD6, 0x39, 0x01, 0x00, 0x40, 0xC9, 0x4D, 0x48, 0xD6, 0x39, 0x01, 0x00,
                0x40, 0x05, 0x00, 0x02, 0x4A, 0x00, 0x00, 0x00, 0x04, 0x04, 0xCF, 0x40, 0x00, 0x00, 0x35, 0xF7,
                0x0E, 0xB2, 0x11, 0x08, 0x00, 0x09, 0x01, 0x01, 0xD2, 0x13, 0x34, 0x36, 0x31, 0x31, 0x36, 0x38,
                0x37, 0x33, 0x36, 0x36, 0x33, 0x34, 0x37, 0x32, 0x31, 0x34, 0x32, 0x38, 0x33, 0x03, 0x03, 0xCF,
                0x40, 0x00, 0x00, 0x35, 0xF7, 0x0E, 0xB2, 0x0F, 0x01, 0x00, 0x01, 0x05, 0x01, 0xCC, 0x13, 0x71,
                0x2C, 0x30, 0x40, 0x02, 0x00, 0xC3, 0xBC, 0xC0, 0x77, 0x2F, 0x06, 0x00, 0x01, 0x02, 0x00, 0x01, 
                0x02, 0x00
			}; // Unknown Data - Related to EffEvents

			if (mCharacters.size() == 0)
            {
				packet << (uint64_t)0x00;
                packet << (uint8_t)0x00;
            }
			else
				packet.Write(data, 114);

			System::PrintBinary((uint8_t*)packet.GetBuffer().data(), packet.GetBuffer().size(), "List");

			packet << (uint16_t)0x12 << (uint16_t)0x32 << xml << (uint64_t)0;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterSelect(uint16_t pContV, uint16_t pTranV)
		{
			Network::Packet packet(Opcode::SMSG_CHARACTER_SELECTED, pContV, pTranV);
			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterCurrentMap(uint16_t pContV, uint16_t pTranV, const std::string& pMapName, const std::string& pMapId)
		{
			uint8_t data[] = { 0x4A, 0x23, 0xFD, 0x46, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			Network::Packet packet(Opcode::SMSG_TRAVEL_PENDING, pContV, pTranV);
			packet << pMapName << pMapId;
			packet.Write(data, 16);
			packet << std::string("\\world\\areas\\") + pMapId + std::string("\\area.dat\0");

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendTravelStatus(uint16_t pContV, uint16_t pTranV, uint32_t pStatus)
		{
			Network::Packet packet(Opcode::SMSG_TRAVEL_STATUS, pContV, pTranV);
			packet << pStatus;
			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterRegionSpecs(uint16_t pContV, uint16_t pTranV, const std::string& pMapName, const std::string& pMapId)
		{
			Network::Packet packet(Opcode::SMSG_SEND_TO_AREA, pContV, pTranV);
			packet << std::string("AreaServer-") + pMapName + std::string("-") + pMapId + std::string("-1-:areaserver\0");
			Write(packet);
		}
		//---------------------------------------------------------------------
        void Session::SendRejectCharacterSelection(uint16_t pContV, uint16_t pTranV, uint64_t pGuid, uint32_t pError)
        {
            Network::Packet packet (Opcode::SMSG_CHARACTER_REJECT_SELECTION, pContV, pTranV);
            packet << pGuid;
            packet << pError;
            Write(packet);
        }
        //---------------------------------------------------------------------
        void Session::SendToCharacterSelect(uint16_t pContV, uint16_t pTranV)
        {
            Network::Packet packet (Opcode::SMSG_SEND_TO_CHARACTER_SELECT, pContV, pTranV);
            Write(packet);
        }
        //---------------------------------------------------------------------
        void Session::SendCharacterDeleteStatus(uint16_t pContV, uint16_t pTranV, uint64_t pGuid, uint16_t pUnks, uint8_t pUnkb, uint32_t pError)
        {
            Network::Packet packet (Opcode::SMSG_CHARACTER_DELETE_STATUS, pContV, pTranV);
            packet << pGuid;
            packet << pUnks;
            packet << pUnkb;
            packet << pError;
            Write(packet);
        }
        //---------------------------------------------------------------------
	}
}