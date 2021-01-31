#include "pch.h"

#include "../BankManager/IDGenerator.h"
#include "../BankManager/BankPolicy.h"

namespace BankManagerTesting
{
	namespace GeneratorTesting
	{
		TEST(GeneratorTest, TestUniqueValue)
		{
			std::list<std::string> someValues;

			for (int i = 0; i < 100; i++)
			{
				someValues.push_back(IDGenerator::GetAccountUUID());
			}

			auto it = std::unique(someValues.begin(), someValues.end());
			ASSERT_TRUE(it == someValues.end());
		}

		TEST(GeneratorTest, TestSizeAndUniqeCardNumber)
		{
			std::list<std::string> someValues;

			for (int i = 0; i < 1000; i++)
			{
				someValues.push_back(IDGenerator::GetCardNumber());
				EXPECT_EQ(someValues.back().size(), SIZE_OF_CARD_NUMBER);
				EXPECT_TRUE(std::all_of(someValues.back().begin(), someValues.back().end(), ::isdigit));
			}

			auto it = std::unique(someValues.begin(), someValues.end());
			ASSERT_TRUE(it == someValues.end());
		}

		TEST(GeneratorTest, TestSizeAndDigitsPinCode)
		{
			std::list<std::string> someValues;

			for (int i = 0; i < 1000; i++)
			{
				someValues.push_back(IDGenerator::GetPinCode());
				EXPECT_EQ(someValues.back().size(), SIZE_OF_PIN_CODE);
				EXPECT_TRUE(std::all_of(someValues.back().begin(), someValues.back().end(), ::isdigit));
			}
		}
	}
}