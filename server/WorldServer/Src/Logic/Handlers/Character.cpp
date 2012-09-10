
#include <DAO/Character.h>
#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <Game/Character.h>
#include <list>

namespace Swtor
{
    namespace Logic
    {
        //---------------------------------------------------------------------
        void Session::HandleCharacterDelete(Network::Packet& pPacket)
        {
            uint64_t guid;
            pPacket >> guid;

            std::ostringstream os;
            os << "Delete Character | Guid: " << guid;
            System::Log::Debug(os.str());

            for (auto itr = mCharacters.begin(); itr != mCharacters.end(); ++itr)
            {
                if (itr->mId == guid)
                {
                    mCharacters.erase(itr);
                    SendCharacterDeleteStatus(pPacket.TransportV, pPacket.ContentV, guid, 0, 1, 0);
                    return;
                }
            }

            SendCharacterDeleteStatus(pPacket.TransportV, pPacket.ContentV, guid, 0, 0, 1);
        }
        //---------------------------------------------------------------------
        void Session::HandleCharacterCreate(Network::Packet& pPacket)
        {
            Game::Character ch;
            ch.unkBytes.clear();
            ch.unkLongs.clear();

            uint32_t unkcount;

            std::string name;
            pPacket >> name;
            ch.SetName(name);

            pPacket >> ch.mId;
            pPacket >> ch.unkFlags;

            if (ch.unkFlags & 0x80)
                pPacket >> ch.UnkLong1; // ClassID

            if (ch.unkFlags & 0x40)
                pPacket >> ch.UnkLong2; // TemplateID

            if (ch.unkFlags & 0x20)
            {
                pPacket >> ch.UnkLong3; // Parent NodeID (Haven't seen it used yet)
                pPacket >> ch.UnkLong4;
            }

            if (ch.unkFlags & 0x10) // ??
            {
                pPacket >> ch.unkVal;
                pPacket >> unkcount;

                for (uint32_t i = 0; i < unkcount; ++i)
                {
                    uint64_t temp;
                    pPacket >> temp;
                    ch.unkLongs.push_back(temp);
                }
            }

            if (ch.unkFlags & 0x08) // Character Fields
            {
                pPacket >> ch.unkShort;
                pPacket >> ch.unkByte;

                pPacket >> unkcount;

				uint64_t c1, c2;

				pPacket >> Network::Packet::packed >> c1 >> c2;

				for (uint32_t i = 0; i < c2; ++i)
				{
					uint64_t fieldId, fieldT;
					pPacket >> fieldId >> fieldT;

					uint64_t payload;
					switch (fieldT)
					{
						case 1:
						case 5:
						case 14:
						case 15:
						case 16:
						case 19:
							pPacket >> payload;
							break;

						case 2:
							pPacket >> payload;
							break;

						case 18:
							{
								float x, y, z;
								pPacket >> x >> y >> z;
							}
							break;

						case 6:
							{
								uint64_t sLen;
								pPacket >> sLen;
								for (uint64_t l = 0; l < sLen; ++l)
								{
									uint8_t cha;
									pPacket >> cha;
								}
							}
							break;

						case 7:
							{
								uint64_t lTy, lc1, lc2;
								pPacket >> lTy >> lc1 >> lc2;

								for (uint64_t j = 0; j < lc2; ++j)
								{
									uint64_t index, data;
									pPacket >> index >> data;
								}
							}
							break;

						case 8:
							{
								uint64_t lTy,lValTy,lc1,lc2;

								pPacket >> lTy >> lValTy >> lc1 >> lc2;

								for (uint64_t j = 0; j < lc2; ++j)
								{
									uint64_t index, data;
									pPacket >> index >> data;
								}
							}
							break;

						default:
							break;
					
					}
				}


                //for (uint32_t i = 0; i < unkcount; ++i)
                //{
                //    uint8_t temp;
                //    pPacket >> temp;

                //    ch.unkBytes.push_back(temp);
                //}
            }

            mCharacters.push_back(ch);
            //Swtor::Logic::Session::mLastChars.push_back(ch);
            //SendCharacterList(pPacket.TransportV, pPacket.ContentV);
            //SendRejectCharacterSelection(pPacket.ContentV, pPacket.TransportV, ch.mId, 14);
            //SendToCharacterSelect(0, 0);
            SendCharacterSelect(pPacket.TransportV, pPacket.ContentV);
            SendCharacterCurrentMap(pPacket.TransportV, pPacket.ContentV, "ord_resize", "4611686019802843831");
            SendTravelStatus(pPacket.TransportV, pPacket.ContentV, 0);
            SendToCharacterSelect(pPacket.TransportV, pPacket.ContentV);

			auto loader = DAO::Save(mCharacters.back());
			mWorld->GetDatabaseWorkQueue()->Push(loader);
        }
        //---------------------------------------------------------------------
        void Session::HandleCharacterList(Network::Packet& pPacket)
        {
            std::ostringstream os;
            os << "Character list request";
            System::Log::Debug(os.str());

            SendCharacterList(pPacket.TransportV, pPacket.ContentV);
        }
        //---------------------------------------------------------------------
        void Session::HandleCharacterSelect(Network::Packet& pPacket)
        {
            uint64_t guid;
            pPacket >> guid;

            std::ostringstream os;
            os << "Character select request | Guid: " << guid;
            System::Log::Debug(os.str());

            //SendRejectCharacterSelection(pPacket.ContentV, pPacket.TransportV, guid, 14);

            SendCharacterSelect(pPacket.ContentV, pPacket.TransportV);
            SendCharacterCurrentMap(pPacket.ContentV, pPacket.TransportV, "ord_resize", "4611686019802843831");
            SendTravelStatus(pPacket.ContentV, pPacket.TransportV, 1);
            SendCharacterRegionSpecs(pPacket.ContentV, pPacket.TransportV, "ord_resize", "4611686019802843831");
        }
        //---------------------------------------------------------------------
        void Session::HandleCharacterSomething(Network::Packet& pPacket)
        {
        }
        //---------------------------------------------------------------------
        void Session::HandleUnk874B000B(Network::Packet& pPacket)
        {
            /*Game::Character ch;
            ch.mAppearance.clear();
            ch.mInventory.clear();*/

            uint8_t flags, unkval, unkbyte;
            uint16_t unkshort;
            uint32_t unkcount, unkcount2;
            uint64_t Unk1, Unk2, Unk3, Unk4, id, Unk5, Unk6;

            std::list<uint64_t> longlist;
            std::list<uint8_t> bytelist;

            std::string name;
            pPacket >> name;
            //ch.SetName(name);

            pPacket >> id;//ch.mId;

            pPacket >> flags;

            if (flags & 0x80)
                pPacket >> Unk1;

            if (flags & 0x40)
                pPacket >> Unk2;

            if (flags & 0x20)
            {
                pPacket >> Unk3;
                pPacket >> Unk4;
            }

            if (flags & 0x10)
            {
                pPacket >> unkval;
                pPacket >> unkcount;

                for (uint32_t i = 0; i < unkcount; ++i)
                {
                    uint64_t temp;
                    pPacket >> temp;

                    longlist.push_back(temp);
                }
            }

            if (flags & 0x08)
            {
                pPacket >> unkshort;
                pPacket >> unkbyte;

                pPacket >> unkcount2;

                for (uint32_t i = 0; i < unkcount2; ++i)
                {
                    uint8_t temp;
                    pPacket >> temp;

                    bytelist.push_back(temp);
                }
            }

            pPacket >> Unk5 >> Unk6;

            std::ostringstream os;
            os << "Packet 0x874B000B content: " << name << " | " << id << " | " << Unk5 << " | " << Unk6;
            System::Log::Debug(os.str());

            //mCharacters.push_back(ch);

            //SendCharacterList(pPacket.ContentV, pPacket.TransportV);
        }
        //---------------------------------------------------------------------
    }
}