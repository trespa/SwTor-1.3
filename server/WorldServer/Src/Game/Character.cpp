#include <Game/Character.h>
#include <Game/Data/CharacterSpecs.h>

namespace Swtor
{
	namespace Game
	{
		//---------------------------------------------------------------------
		Character::Character()
			:mName("PlaceHolder"),
			 mLevel(0x1),
			 mGender(0xE2)
		{
			mId = 0;
			unkFlags = 0;
			unkByte = 0;
			unkVal = 0;
			UnkLong1 = UnkLong2 = UnkLong3 = UnkLong4 = 0;
			unkBytes.clear();
			unkLongs.clear();

			mRegion = 0x11c6f45500000040;

			mSpec1 = 0x4e7511aa;
			mSpec2 = 0x899;
			mSpec3 = 0x80;

			mApp1 = 0xdb43f674;
			mApp2 = 0x4d0e94dc;
			mApp3 = 0xb19c6ccb;
			mApp4 = 0x1a7;

			mAppearance[0x01] = 0x1504;
			mAppearance[0x05] = 0x2004;
			mAppearance[0x07] = 0x1D04;
			mAppearance[0x09] = 0xAB04;
			mAppearance[HAIR_TYPE] = 0xD204;
			mAppearance[HAIR_COLOR] = 0x0C05;
			mAppearance[FACE_FORM] = 0x2204;
			mAppearance[SKIN_COLOR] = 0x1804;

			mInventory.push_back(0x9fb9e47a404900e0);
			mInventory.push_back(0x3d83c0d0b11b00e0);
			mInventory.push_back(0xBF8910d4d6fa00e0);

			for(int i = 0; i < 8; ++i)
				((uint8_t*)&mClass)[i] = ((uint8_t*)&SithWarrior)[7-i];
		}
		//---------------------------------------------------------------------
		void Character::SetName(const std::string& pName)
		{
			mName = pName;
		}
		//---------------------------------------------------------------------
		std::string Character::GetName()
		{
			return mName;
		}
		//---------------------------------------------------------------------
		void Character::SetLevel(uint8_t pLevel)
		{
			mLevel = pLevel;
		}
		//---------------------------------------------------------------------
		uint8_t Character::GetLevel()
		{
			return mLevel;
		}
		//---------------------------------------------------------------------
	}
}