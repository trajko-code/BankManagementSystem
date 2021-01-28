#include "pch.h"

#include "../BankManager/Client.h"
#include "../BankManager/IDatabase.h"
#include "../BankManager/ClientDataConstants.h"

namespace ClientTesting
{
	class DatabaseConnectorMock : public IDatabase
	{
	public:
		MOCK_METHOD(bool, Connect, (), (override));
		MOCK_METHOD(bool, Disconnect, (), (override));
		MOCK_METHOD(bool, IsConnected, (), (override));
		MOCK_METHOD(int, Query, (std::string query), (override));
		MOCK_METHOD(std::string, Query, (int query), (override));
	};

	class ClientTest : public ::testing::Test
	{
		protected:
			void SetUp() override
			{
				::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
				_client = std::unique_ptr<Client::Client>(
					new Client::Client(&databaseConnection, "Milica", "Aleksinac", "0658878114", "22/03/1997",
										"2203997736317", "4514254758962551", "2203"));
			}

			void TearDown() override
			{
			}

			std::unique_ptr<Client::Client> _client;
	};

	TEST_F(ClientTest, TestInitialValues)
	{
		int cardNumberLength = CARD_NUMBER_LENGTH;
		EXPECT_EQ(cardNumberLength, _client->GetCardNumber().length());
		int pinCodeLength = PIN_CODE_LENGTH;
		EXPECT_EQ(pinCodeLength, _client->GetPinCode().length());
		int personIdNumberLength = PERSON_ID_NUMBER_LENGTH
		EXPECT_EQ(personIdNumberLength, _client->GetPersonIdentifactionNumber().length());
		
		EXPECT_LT(1, _client->GetName().length());
		EXPECT_LT(2, _client->GetAddress().length());
		EXPECT_LT(5, _client->GetPhoneNumber().length());
		EXPECT_LT(7, _client->GetDateOfBirth().length());
	}


}