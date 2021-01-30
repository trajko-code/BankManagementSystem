#include "pch.h"

#include "../BankManager/ClientManager.h"
#include "../BankManager/ClientExists.h"
#include "../BankManager/ClientNotExists.h"
#include "../BankManager/UnableToConnect.h"

namespace ClientManagerTesting
{
	class DatabaseConnectorMock : public IDatabase
	{
	public:
		MOCK_METHOD(bool, Connect, (), (override));
		MOCK_METHOD(bool, Disconnect, (), (override));
		MOCK_METHOD(bool, IsConnected, (), (override));
		MOCK_METHOD(void, AddNew, (std::shared_ptr<Client::Client> client), (override));
		MOCK_METHOD(void, Update, (std::shared_ptr<Client::Client> client), (override));
		MOCK_METHOD(void, UpdateClientAccount, (std::shared_ptr<Client::Client> client, std::string accId), (override));
		MOCK_METHOD(bool, CheckIfClientExists, (std::string persionIdentificationNumber), (override));
		MOCK_METHOD(std::shared_ptr<Client::Client>, Load, (std::string cardNumber, std::string pinCode), (override));
		MOCK_METHOD(std::shared_ptr<Client::Client>, Load, (std::string clientId), (override));
	};

	TEST(ClientManagerTest, TestConstructorAndDestructor)
	{
		::testing::StrictMock<DatabaseConnectorMock> databaseConnection;

		EXPECT_CALL(databaseConnection, Connect())
			.Times(1);

		Client::ClientManager manager(&databaseConnection);

		::testing::InSequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Disconnect());
	}

	TEST(ClientManagerTest, AddNewClientConnectedAndExists)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())		
			.Times(::testing::Exactly(1))
			.InSequence(seq)
			.WillOnce(::testing::Return(true));

		ON_CALL(databaseConnection, CheckIfClientExists(::testing::_))
			.WillByDefault(::testing::Return(true));
		EXPECT_CALL(databaseConnection, CheckIfClientExists(::testing::_))		
			.InSequence(seq);
		
		ASSERT_THROW(manager.AddNewClient("Nikola", "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", "1234567891234567", "0101"), Database::dbExceptions::ClientExists);
	
		EXPECT_CALL(databaseConnection, IsConnected());
	}

	TEST(ClientManagerTest, AddNewClientNotConnected)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		::testing::InSequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, Connect())
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, CheckIfClientExists(::testing::_))
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, AddNew(::testing::_));

		manager.AddNewClient("Nikola", "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", "1234567891234567", "0101");

		//Expect calls in destructor
		EXPECT_CALL(databaseConnection, IsConnected())
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Disconnect());
	}

	TEST(ClientManagerTest, AddNewClientTryToConnect)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.InSequence(seq)
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, Connect())	
			.Times(3)
			.InSequence(seq)
			.WillRepeatedly(::testing::Return(false));

		ASSERT_THROW(manager.AddNewClient("Nikola", "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", "1234567891234567", "0101"), Database::dbExceptions::UnableToConnect);
	
		::testing::Mock::VerifyAndClearExpectations(&databaseConnection);
	}

	TEST(ClientManagerTest, LoadClientConnected)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		std::string name = "Nikola";
		std::string cardNumber = "0101010278457854";
		std::shared_ptr<Client::Client> client = std::make_shared<Client::Client>(name, "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", cardNumber, "0101");

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.InSequence(seq)
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Load(cardNumber))
			.InSequence(seq)
			.WillOnce(::testing::Return(client));

		manager.LoadClient(cardNumber);

		ASSERT_EQ(name, manager.GetClientName());

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, LoadClientNotConnected)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		std::string name = "Nikola";
		std::string address = "Aleksinac";
		std::string cardNumber = "0101010278457854";
		std::shared_ptr<Client::Client> client = std::make_shared<Client::Client>(name, address, "060111222", "01.01.1997.",
			"0101997561514", cardNumber, "0101");

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.InSequence(seq)
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, Connect())
			.InSequence(seq)
			.WillOnce(::testing::Return(false))
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Load(cardNumber))
			.InSequence(seq)
			.WillOnce(::testing::Return(client));

		manager.LoadClient(cardNumber);

		ASSERT_EQ(name, manager.GetClientName());
		ASSERT_EQ(address, manager.GetClientAddress());

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, LoadClientNotExists)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);;

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.InSequence(seq)
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Load(::testing::_))
			.InSequence(seq)
			.WillOnce(::testing::ReturnNull());

		ASSERT_THROW(manager.LoadClient("0123547854862145"), Database::dbExceptions::ClientNotExists);

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, AuthenticateClientSuccesful)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		std::string cardNumber = "0101010278457854";
		std::string pinCode = "0101";

		std::shared_ptr<Client::Client> client = std::make_shared<Client::Client>(
			"Nikola", "Aleksinac", "060111222", "01.01.1997.", 
			"0101997561514", cardNumber, pinCode);

		::testing::InSequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.Times(::testing::Exactly(1))
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, Connect())
			.Times(::testing::AtLeast(1))
			.WillOnce(::testing::Return(false))
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Load(cardNumber, pinCode))
			.Times(::testing::Exactly(1))
			.WillOnce(::testing::Return(client));

		ASSERT_TRUE(manager.AuthenticateClient(cardNumber, pinCode));
		ASSERT_EQ(cardNumber, manager.GetClientCardNumber());
		ASSERT_EQ(pinCode, manager.GetClientPinCode());

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, AuthenticateClientFailed)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		std::string cardNumber = "0101010278457854";
		std::string pinCode = "0101";

		::testing::InSequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.Times(::testing::Exactly(1))
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Load(cardNumber, pinCode))
			.Times(::testing::Exactly(1))
			.WillOnce(::testing::ReturnNull());

		ASSERT_FALSE(manager.AuthenticateClient(cardNumber, pinCode));

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, UpdateClientDataNotChanged)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		ON_CALL(databaseConnection, IsConnected())
			.WillByDefault(::testing::Return(true));
		ON_CALL(databaseConnection, Connect())
			.WillByDefault(::testing::Return(true));

		std::string name = "Nikola";
		std::string cardNumber = "0101010278457854";
		std::shared_ptr<Client::Client> client = std::make_shared<Client::Client>(name, "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", cardNumber, "0101");

		std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> accounts = std::make_shared<std::vector<std::shared_ptr<Account::Account>>>();
		std::shared_ptr<Account::Account> account = std::make_shared<Account::Account>(Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd);
		accounts->push_back(account);
		client->SetClientAccounts(accounts);

		ON_CALL(databaseConnection, Load(cardNumber))
			.WillByDefault(::testing::Return(client));

		manager.LoadClient(cardNumber);

		ASSERT_EQ(name, manager.GetClientName());
		ASSERT_EQ(client->GetAccounts()->size(), manager.GetClientAccounts()->size());

		::testing::Sequence seq1;

		EXPECT_CALL(databaseConnection, IsConnected())
			.Times(::testing::Exactly(0));
		EXPECT_CALL(databaseConnection, Connect())
			.Times(::testing::Exactly(0));
		EXPECT_CALL(databaseConnection, Update(::testing::_))
			.Times(::testing::Exactly(0));

		manager.UpdateClient();

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}

	TEST(ClientManagerTest, UpdateClientDataChanged)
	{
		::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
		Client::ClientManager manager(&databaseConnection);

		ON_CALL(databaseConnection, IsConnected())
			.WillByDefault(::testing::Return(true));
		ON_CALL(databaseConnection, Connect())
			.WillByDefault(::testing::Return(true));

		std::string name = "Nikola";
		std::string cardNumber = "0101010278457854";
		std::shared_ptr<Client::Client> client = std::make_shared<Client::Client>(name, "Aleksinac", "060111222", "01.01.1997.",
			"0101997561514", cardNumber, "0101");

		std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> accounts = std::make_shared<std::vector<std::shared_ptr<Account::Account>>>();
		std::shared_ptr<Account::Account> account = std::make_shared<Account::Account>(Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd);
		accounts->push_back(account);
		client->SetClientAccounts(accounts);

		ON_CALL(databaseConnection, Load(cardNumber))
			.WillByDefault(::testing::Return(client));

		manager.LoadClient(cardNumber);

		ASSERT_EQ(name, manager.GetClientName());
		ASSERT_EQ(client->GetAccounts()->size(), manager.GetClientAccounts()->size());

		auto acc = manager.GetClientAccounts()->back();
		manager.DepositOnClientAccount(acc->GetAccountId(), 500.0f);

		::testing::Sequence seq;

		EXPECT_CALL(databaseConnection, IsConnected())
			.InSequence(seq)
			.WillOnce(::testing::Return(false));
		EXPECT_CALL(databaseConnection, Connect())
			.Times(3)
			.InSequence(seq)
			.WillOnce(::testing::Return(false))
			.WillOnce(::testing::Return(false))
			.WillOnce(::testing::Return(true));
		EXPECT_CALL(databaseConnection, Update(::testing::_))
			.Times(::testing::Exactly(1))
			.InSequence(seq);

		manager.UpdateClient();

		::testing::Mock::VerifyAndClear(&databaseConnection);
	}
}