#pragma once

#include <Logic/Session.h>
#include <Game/Service/CharacterService.h>

namespace Swtor{
	namespace Game
	{
		class World 
		{
		public:

			World();

		protected:
		private:

			Service::CharacterService mCharacterService;
		};
	}
}
