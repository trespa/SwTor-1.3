#pragma once

#include <Game/Character.h>
#include <Logic/Account.h>
#include <DAO/DAO.h>
#include <System/Log.h>

namespace Swtor{
	namespace DAO
	{
		template <>
		inline void DAO<Logic::Account>::Load(SimpleDB::Database& pDatabase)
		{
			try
			{
				std::ostringstream oss;
				oss << "SELECT swtor_user.id, users.user_username, users.user_level FROM swtor_user"
					<< " LEFT JOIN users ON swtor_user.id=users.id"
					<< " WHERE server_id='" 
					<< pDatabase.escapeString(mEntity.User)<< "';";


				SimpleDB::Query query(pDatabase);
				SimpleDB::StringColumn user(61);
				SimpleDB::IntColumn id,level;
				SimpleDB::Column * cols[] = {&id,&user,&level};
				query.bind(cols,3);
				query.execute(oss.str());

				if(query.fetchRow())
				{
					mEntity.User = user.value();
					mEntity.Level = level.value();
					mEntity.Id = id.value();

					OnEvent(IDAO::LOAD, true);
				}
				else
					throw std::runtime_error("Account not found");
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
				OnEvent(IDAO::LOAD, false);
			}			
		}

		template <>
		inline void DAO<Logic::Account>::Save(SimpleDB::Database& pDatabase)
		{
			try
			{
				pDatabase.voidQuery(mEntity.Sqlstr);
			}
			catch(std::exception& e)
			{
				Swtor::System::Log::GetInstance()->Error(e.what());
			}

			//NotifySave();
		}
	}
}