#pragma once

#include "..\Game\IWorld.h"

namespace Swtor
{
	namespace Script
	{
		class Plugin
		{
		public:

			// If one plugin returns true then it will cancel the event !

			virtual void OnEnable() = 0;
			virtual void OnDisable() = 0;
			virtual void OnNewShard(Game::IWorld*) = 0;
		};
	}
}