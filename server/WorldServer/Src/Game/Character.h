#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <vector>

namespace Swtor
{
	namespace Game
	{
		/**
		 * Character manager and holder
		 */
		class Character
		{
		public:

			/**
			 * @brief Constructor
			 */
			Character();

			/**
			 * @brief Set the character's name
			 * @param pName The name to set
			 * @return
			 */
			void		SetName(const std::string& pName);

			/**
			 * @brief Get the character's name
			 * @return The character's name
			 */
			std::string	GetName();

			/**
			 * @brief Set the character's level
			 * @param pLevel The level to set
			 * @return
			 */
			void		SetLevel(uint8_t pLevel);


			/**
			 * @brief Get the character's level
			 * @return The character's level
			 */
			uint8_t		GetLevel();

		private:

			std::string mName;
			uint8_t mLevel;

		public:
			uint64_t mId;
			uint8_t unkFlags, unkVal, unkByte;
			uint16_t unkShort;

			uint64_t UnkLong1, UnkLong2, UnkLong3, UnkLong4;

			std::vector<uint8_t> unkBytes;
			std::vector<uint64_t> unkLongs;

			std::map<uint8_t, uint16_t> mAppearance;
			std::vector<uint64_t> mInventory;

			uint32_t mRandomPayload;
			uint8_t mGender;
			uint8_t mPayload[12];

			uint64_t mRegion;
			uint64_t mClass;

			uint32_t mSpec1;
			uint32_t mSpec2;
			uint8_t  mSpec3;
			uint16_t mSpec4;
			uint8_t  mSpec5;

			uint32_t mApp1;
			uint32_t mApp2;
			uint32_t mApp3;
			uint16_t mApp4;
		};
	}
}