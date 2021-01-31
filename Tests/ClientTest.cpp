#include "pch.h"

#include "../BankManager/Client.h"
#include "../BankManager/IDatabase.h"
#include "../BankManager/ClientDataConstants.h"
#include "../BankManager/AccountType.h"
#include "../BankManager/Account.h"
#include "../BankManager/CurrencyType.h"
#include "../BankManager/InvalidDeleteAccount.h"
#include "../BankManager/AccountTypeExists.h"

namespace BankManagerTesting
{
	namespace ClientTesting
	{
		class ClientTest : public ::testing::Test
		{
		protected:
			void SetUp() override
			{
				_client = std::unique_ptr<Client::Client>(
					new Client::Client("Milica", "Aleksinac", "0658878114", "22/03/1997",
						"2203997736317", "4514254758962551", "2203"));

				_client->CreateAccount(Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd);
				_client->CreateAccount(Account::AccountType::ForeignChecking, Account::CurrencyType::Eur);
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

		TEST_F(ClientTest, CreateAccount)
		{
			int accNum = _client->GetAccounts()->size();
			_client->CreateAccount(Account::AccountType::Savings, Account::CurrencyType::Rsd);
			EXPECT_EQ(_client->GetAccounts()->size(), accNum + 1);
		}

		TEST_F(ClientTest, CreateAccountConstraint)
		{
			ASSERT_THROW(_client->CreateAccount(Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd),
				Client::clExceptions::AccountTypeExists);
			ASSERT_THROW(_client->CreateAccount(Account::AccountType::ForeignChecking, Account::CurrencyType::Eur),
				Client::clExceptions::AccountTypeExists);
		}

		TEST_F(ClientTest, DepositOnAccount)
		{
			float amountToAdd = 200.0f;
			for (auto acc = _client->GetAccounts()->begin(); acc != _client->GetAccounts()->end(); acc++)
			{
				float amountBefore = (*acc)->GetBalance();
				_client->DepositOnAccount((*acc)->GetAccountId(), amountToAdd);
				EXPECT_EQ(amountBefore + amountToAdd, (*acc)->GetBalance());
			}
		}

		TEST_F(ClientTest, DepositOnAccountUpdateTotalAmount)
		{
			float totalBegin = _client->GetTotalAmount(Account::CurrencyType::Rsd);

			float amountToAdd = 200.0f;
			auto acc = std::find_if(_client->GetAccounts()->begin(), _client->GetAccounts()->end(),
				[](const std::shared_ptr<Account::Account>& a) { return a->GetCurrencyType() == Account::CurrencyType::Rsd; });

			_client->DepositOnAccount((*acc)->GetAccountId(), amountToAdd);

			ASSERT_FLOAT_EQ(totalBegin + amountToAdd, _client->GetTotalAmount(Account::CurrencyType::Rsd));

			totalBegin = _client->GetTotalAmount(Account::CurrencyType::Eur);

			acc = std::find_if(_client->GetAccounts()->begin(), _client->GetAccounts()->end(),
				[](const std::shared_ptr<Account::Account>& a) { return a->GetCurrencyType() == Account::CurrencyType::Eur; });

			_client->DepositOnAccount((*acc)->GetAccountId(), amountToAdd);

			ASSERT_FLOAT_EQ(totalBegin + amountToAdd, _client->GetTotalAmount(Account::CurrencyType::Eur));
		}

		TEST_F(ClientTest, WithdrawFromAccount)
		{
			float totalBegin = _client->GetTotalAmount(Account::CurrencyType::Rsd);

			auto acc = std::find_if(_client->GetAccounts()->begin(), _client->GetAccounts()->end(),
				[](const std::shared_ptr<Account::Account>& a) { return a->GetCurrencyType() == Account::CurrencyType::Rsd; });

			float amountOnAccountBegin = (*acc)->GetBalance();
			float amountToAdd = 200.0f;
			_client->DepositOnAccount((*acc)->GetAccountId(), amountToAdd);
			float amountToWithdraw = 100.0f;
			_client->WithdrawFromAccount((*acc)->GetAccountId(), amountToWithdraw);

			ASSERT_FLOAT_EQ(amountOnAccountBegin + amountToAdd - amountToWithdraw, (*acc)->GetBalance());
			ASSERT_FLOAT_EQ(totalBegin + amountToAdd - amountToWithdraw, _client->GetTotalAmount(Account::CurrencyType::Rsd));

			_client->CreateAccount(Account::AccountType::CertificateOfDeposit, Account::CurrencyType::Chf);
			totalBegin = _client->GetTotalAmount(Account::CurrencyType::Chf);

			acc = std::find_if(_client->GetAccounts()->begin(), _client->GetAccounts()->end(),
				[](const std::shared_ptr<Account::Account>& a) { return a->GetCurrencyType() == Account::CurrencyType::Chf; });

			amountOnAccountBegin = (*acc)->GetBalance();
			amountToAdd = 200.0f;
			_client->DepositOnAccount((*acc)->GetAccountId(), amountToAdd);
			amountToWithdraw = 100.0f;
			_client->WithdrawFromAccount((*acc)->GetAccountId(), amountToWithdraw);

			ASSERT_FLOAT_EQ(amountOnAccountBegin + amountToAdd - amountToWithdraw, (*acc)->GetBalance());
			ASSERT_FLOAT_EQ(totalBegin + amountToAdd - amountToWithdraw, _client->GetTotalAmount(Account::CurrencyType::Chf));
		}

		TEST_F(ClientTest, DeleteAccountNotEmpty)
		{
			std::shared_ptr<Account::Account> acc = _client->GetAccounts()->back();
			_client->DepositOnAccount(acc->GetAccountId(), 200.0f);

			EXPECT_THROW(_client->DeleteAccount(acc->GetAccountId()), Client::clExceptions::InvalidDeleteAccount);
		}

		TEST_F(ClientTest, DeleteAccount)
		{
			int accNum = _client->GetAccounts()->size();
			std::shared_ptr<Account::Account> acc = _client->GetAccounts()->back();
			_client->DeleteAccount(acc->GetAccountId());

			ASSERT_EQ(accNum - 1, _client->GetAccounts()->size());
		}
	}
}