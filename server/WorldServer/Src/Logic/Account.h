#pragma once

namespace Swtor{
	namespace Logic
	{
		class Account
		{
		public:

			Account()
				:Banned(false),Id(0),Level(0)
			{
			}

			bool Banned;
			uint32_t Level;
			std::string User;
			std::string SessionId;
			std::string ServerId;
			std::string Sqlstr;
			uint32_t Id;
		};
	}
}