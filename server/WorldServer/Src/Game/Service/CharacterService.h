#pragma once

#include <Logic/Session.h>
#include <Game/Character.h>

namespace Swtor{ namespace Game {
	namespace Service{

		class CharacterService
		{
		public:

		protected:

		private:

			typedef std::list<Character> CharacterList;
			typedef std::map<Logic::Session::pointer,  CharacterList> mCharacters;
		};

	}
}}

