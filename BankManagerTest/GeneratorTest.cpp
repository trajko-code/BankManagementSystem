#include "pch.h"

#include "../BankManager/UUIDGenerator.h"

namespace GeneratorTesting
{
	TEST(GeneratorTest, TestUniqueValue)
	{
		std::list<std::string> someValues;

		for (int i = 0; i < 100; i++)
		{
			someValues.push_back(UUIDGenerator::GetAccountUUID());
		}

		auto it = std::unique(someValues.begin(), someValues.end());
		ASSERT_TRUE(it == someValues.end());
	}
}