#pragma once

namespace Swtor{
	namespace Entity
	{
		class Account
		{
		public:

			Account()
				:Banned(false),Id(0)
			{
			}

			bool Banned;
			uint32_t Level;
			std::string User;
			std::string SessionId;
			std::string ServerId;
			uint32_t Id;
		};
	}
}