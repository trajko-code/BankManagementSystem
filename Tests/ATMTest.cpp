#include "pch.h"

#include "../ATMManager/ATM.h"
#include "../ATMManager/KeyCodes.h"
#include "../ATMManager/ATMMessages.h"
#include "../ATMManager/ICreditCardReader.h"
#include "../ATMManager/IDeployControl.h"
#include "../ATMManager/IDisplay.h"
#include "../ATMManager/IKeyBoard.h"
#include "../BankManager/Account.h"
#include "../BankManager/AccountType.h"
#include "../BankManager/CurrencyType.h"

namespace ATMManagerTesting
{
	namespace ATMTesting
	{
		class ClientManagerMock
		{
		public:
			MOCK_METHOD(bool, AuthenticateClient, (const std::string cardNumber, const std::string pinCode), ());
			MOCK_METHOD(void, UpdateClient, (), ());
			MOCK_METHOD(void, WithdrawFromClientAccount, (const std::string accId, const float amount), ());
			MOCK_METHOD(std::shared_ptr<Account::Account>, GetClientAccount, (const std::string accId), (const));
		};
		
		class CreditCardReaderMock : public ManufacturerAPI::ICreditCardReader
		{
		public:
			MOCK_METHOD(void, CreditCardInserted, ((std::function<void(std::string cardNumber, std::string accountId)> cbFunciton)), (override));
			MOCK_METHOD(void, EjectCreditCard, (), (override));
		};
		
		class DeployControlMock : public ManufacturerAPI::IDeployControl
		{
		public:
			MOCK_METHOD(void, DeployCash, (int deployAmount), (override));
			MOCK_METHOD(bool, IsCashDeployed, (), (override));
		};
		
		class DisplayMock : public ManufacturerAPI::IDisplay
		{
		public:
			MOCK_METHOD(void, DisplayText, (const std::string text_to_display), (override));
		};
		
		class KeyboardMock : public ManufacturerAPI::IKeyboard
		{
		public:
			MOCK_METHOD(void, KeypadSetOnKeyPressed, (std::function<void(ATM::KEY_t)> keyPressCallback), (override));
		};

		class ATMTest : public ::testing::Test
		{
			protected:
				void SetUp() override
				{
					_atm = std::make_unique<ATM::ATM<::testing::NiceMock<ClientManagerMock>>>(&clientManager, &cardReader, &deployControl, &display, &keyboard);
				}
				void TearDown() override
				{

				}

				::testing::NiceMock<ClientManagerMock> clientManager;
				::testing::NiceMock<CreditCardReaderMock> cardReader;
				::testing::NiceMock<DeployControlMock> deployControl;
				::testing::NiceMock<DisplayMock> display;
				::testing::NiceMock<KeyboardMock> keyboard;
				std::unique_ptr<ATM::ATM<::testing::NiceMock<ClientManagerMock>>> _atm;

				std::string cardNumber = "0124875986520154";
				std::string accountId = "ACC0221547524552";
		};

		TEST_F(ATMTest, AuthentificationFailed)
		{
			::testing::InSequence seq;

			EXPECT_CALL(display, DisplayText(INSERT_CARD));

			EXPECT_CALL(cardReader, CreditCardInserted(::testing::_))
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(cardNumber, accountId));

			EXPECT_CALL(display, DisplayText(INSERT_PIN));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::AtLeast(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Five))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Eight))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Two))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Enter));

			EXPECT_CALL(clientManager, AuthenticateClient)
				.WillOnce(::testing::Return(false));

			EXPECT_CALL(display, DisplayText(AUTHENTIFICATION_FAILED));

			EXPECT_CALL(cardReader, EjectCreditCard)
				.Times(1);

			_atm->Run();
		}

		TEST_F(ATMTest, ClickedCancelButton)
		{
			::testing::InSequence seq;

			EXPECT_CALL(display, DisplayText(INSERT_CARD));

			EXPECT_CALL(cardReader, CreditCardInserted(::testing::_))
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(cardNumber, accountId));

			EXPECT_CALL(display, DisplayText(INSERT_PIN));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::AtLeast(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Cancel));

			EXPECT_CALL(display, DisplayText(PRESSED_CANCEL));

			EXPECT_CALL(cardReader, EjectCreditCard)
				.Times(1);

			_atm->Run();
		}

		TEST_F(ATMTest, AuthentificationSuccess)
		{
			::testing::InSequence seq;

			EXPECT_CALL(display, DisplayText(INSERT_CARD));

			EXPECT_CALL(cardReader, CreditCardInserted(::testing::_))
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(cardNumber, accountId));

			EXPECT_CALL(display, DisplayText(INSERT_PIN));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(5))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Three))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Eight))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Two))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Enter));

			EXPECT_CALL(clientManager, AuthenticateClient)
				.WillOnce(::testing::Return(true));
			
			EXPECT_CALL(display, DisplayText(AUTHENTIFICATION_SUCCESS));
			EXPECT_CALL(display, DisplayText(USER_OPTIONS));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Cancel));

			EXPECT_CALL(display, DisplayText(PRESSED_CANCEL));

			EXPECT_CALL(cardReader, EjectCreditCard)
				.Times(1);
			
			_atm->Run();
		}

		TEST_F(ATMTest, UserOption1)
		{
			std::shared_ptr<Account::Account> acc = std::make_shared<Account::Account>(
				Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd);
			float amount = 4500.0f;
			acc->Deposit(amount);

			::testing::InSequence seq;

			EXPECT_CALL(display, DisplayText(INSERT_CARD));

			EXPECT_CALL(cardReader, CreditCardInserted(::testing::_))
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(cardNumber, accountId));

			EXPECT_CALL(display, DisplayText(INSERT_PIN));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(5))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Three))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Eight))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Two))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Enter));

			EXPECT_CALL(clientManager, AuthenticateClient)
				.WillOnce(::testing::Return(true));

			EXPECT_CALL(display, DisplayText(AUTHENTIFICATION_SUCCESS));
			EXPECT_CALL(display, DisplayText(USER_OPTIONS));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Option1));

			EXPECT_CALL(display, DisplayText(OPTION1));

			EXPECT_CALL(clientManager, GetClientAccount)
				.WillOnce(::testing::Return(acc));

			EXPECT_CALL(display, DisplayText(std::to_string(amount)));

			_atm->Run();
		}

		TEST_F(ATMTest, UserOption2)
		{
			std::shared_ptr<Account::Account> acc = std::make_shared<Account::Account>(
				Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd);
			float amount = 4500.0f;
			acc->Deposit(amount);

			::testing::InSequence seq;

			EXPECT_CALL(display, DisplayText(INSERT_CARD));

			EXPECT_CALL(cardReader, CreditCardInserted(::testing::_))
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(cardNumber, accountId));

			EXPECT_CALL(display, DisplayText(INSERT_PIN));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(5))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Three))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Eight))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Two))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Enter));

			EXPECT_CALL(clientManager, AuthenticateClient)
				.WillOnce(::testing::Return(true));

			EXPECT_CALL(display, DisplayText(AUTHENTIFICATION_SUCCESS));
			EXPECT_CALL(display, DisplayText(USER_OPTIONS));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::Exactly(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Option2));;

			EXPECT_CALL(display, DisplayText(OPTION2));

			EXPECT_CALL(keyboard, KeypadSetOnKeyPressed)
				.Times(::testing::AtLeast(1))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::One))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Nine))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Four))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Five))
				.WillOnce(::testing::InvokeArgument<0>(ATM::KEY_t::Enter));

			EXPECT_CALL(deployControl, DeployCash(1945));

			EXPECT_CALL(deployControl, IsCashDeployed)
				.WillOnce(::testing::Return(true));

			EXPECT_CALL(clientManager, WithdrawFromClientAccount(::testing::_, ::testing::Le(amount)))
				.Times(::testing::Exactly(1));

			EXPECT_CALL(display, DisplayText(WITHDRAW_SUCCESS));

			_atm->Run();
		}
	}
}
