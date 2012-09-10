#pragma once

#include <Game/Character.h>
#include <DAO/DAO.h>
#include <System/Log.h>

namespace Swtor{
	namespace DAO
	{
		template <>
		inline void DAO<Game::Character>::Load(SimpleDB::Database& pDatabase)
		{
			try
			{
				/*std::ostringstream oss;
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
					throw std::runtime_error("Account not found");*/
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
				OnEvent(IDAO::LOAD, false);
			}			
		}

		template <>
		inline void DAO<Game::Character>::Save(SimpleDB::Database& pDatabase)
		{
			try
			{
				std::ostringstream oss;
				oss << "INSERT INTO `swtor_character` (`ch_id`, `ch_name`, `ch_Level`, `UnkLong1`, `UnkLong2`, `UnkLong3`, `UnkLong4`, `ch_Gender`, `ch_Region`, `ch_Class`, `ch_Spec1`, `ch_Spec2`, `ch_Spec3`, `ch_Spec4`, `ch_Spec5`, `ch_App1`, `ch_App2`, `ch_App3`, `ch_App4`) VALUES (NULL , '" 
					<< mEntity.GetName().c_str() << "', '" 
					<< (int)mEntity.GetLevel() << "', '" 
					<< mEntity.UnkLong1 << "', '" 
					<< mEntity.UnkLong2 << "', '" 
					<< mEntity.UnkLong3 << "', '" 
					<< mEntity.UnkLong4 << "', '" 
					<< (int)mEntity.mGender << "', '" 
					<< (int)mEntity.mRegion <<  "', '" 
					<< (int)mEntity.mClass <<  "', '" 
					<< (int)mEntity.mSpec1 <<  "', '" 
					<< (int)mEntity.mSpec2 <<  "', '" 
					<< (int)mEntity.mSpec3 <<  "', '" 
					<< (int)mEntity.mSpec4 <<  "', '" 
					<< (int)mEntity.mSpec5 <<  "', '" 
					<< (int)mEntity.mApp1 <<  "', '" 
					<< (int)mEntity.mApp2 <<  "', '" 
					<< (int)mEntity.mApp3 <<  "', '" 
					<< (int)mEntity.mApp4 << "');" 
					<< endl;

				pDatabase.voidQuery(oss.str());
			}
			catch(std::exception& e)
			{
				Swtor::System::Log::GetInstance()->Error(e.what());
			}
		}
	}
}