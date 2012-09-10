#pragma once

#include <cstdint>
#include <bullet/btBulletCollisionCommon.h>

namespace Swtor
{
	namespace Game
	{
		enum Appearance
		{
			HAIR_TYPE   = 0x0B,
			HAIR_COLOR = 0x0C,
			FACE_FORM = 0x0E,
			SKIN_COLOR = 0x10
		};

		static const uint64_t JediKnight = 16141119516274073244ULL;
		static const uint64_t JediConsular = 16141179471541245792ULL;
		static const uint64_t Smuggler = 16140912704077491401ULL;
		static const uint64_t Trooper = 16140973599688231714ULL;
		static const uint64_t SithWarrior = 16140902893827567561ULL;
		static const uint64_t SithInquisitor = 16141010271067846579ULL;
		static const uint64_t BountyHunter = 16141170711935532310ULL;
		static const uint64_t ImperialAgent = 16140943676484767978ULL;
		// Advanced Classes
		static const uint64_t JediSentinel = 16140943676484767978ULL + 1;
		static const uint64_t JediGuardian = 16140943676484767978ULL + 2;
		static const uint64_t JediSage = 16140943676484767978ULL + 3;
		static const uint64_t JediShadow = 16140943676484767978ULL + 4;
		static const uint64_t Gunslinger = 16140943676484767978ULL + 5;
		static const uint64_t Scoundrel = 16140943676484767978ULL + 6;
		static const uint64_t Commando = 16140943676484767978ULL + 7;
		static const uint64_t Vanguard = 16140943676484767978ULL + 8;
		static const uint64_t SithJuggernaut = 16140943676484767978ULL + 9;
		static const uint64_t SithMarauder = 16140943676484767978ULL + 10;
		static const uint64_t SithAssassin = 16140943676484767978ULL + 11;
		static const uint64_t SithSorcerer = 16140943676484767978ULL + 12;
		static const uint64_t Powertech = 16140943676484767978ULL + 13;
		static const uint64_t Mercenary = 16140943676484767978ULL + 14;
		static const uint64_t Operative = 16140943676484767978ULL + 15;
		static const uint64_t Sniper = 16140943676484767978ULL + 16;
	}
}
