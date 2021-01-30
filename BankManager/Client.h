#pragma once

#define CLIENT_API _declspec(dllexport)

#include "pch.h"
#include "Account.h"
#include "Credit.h"
#include "AccountType.h"
#include "CurrencyType.h"

namespace Client
{
	class CLIENT_API Client
	{
		protected:	
			std::string clientId;
			std::string name;
			std::string address;
			std::string phoneNumber;
			std::string dateOfBirth;
			std::string personIdentifactionNumber;
			std::string cardNumber;
			std::string pinCode;
			float totalAmount; //in domestic currency
			std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> client_accounts;
			std::vector<Credit::Credit> client_credits;

		private:
			bool changedData;

		public:
			/**
			 * @brief Default contstructor
			 *
			 * @exception Client::clExceptions::EmptyInitialValues if any parameter is empty string
			 * @exception Client::clExceptions::InvalidValue if person identification number, card number and pin code has invalid length.
			 */
			Client(std::string Name, std::string Address, std::string PhoneNumber, 
					std::string DateOfBirth, std::string PersonIdentificationNumber, 
					std::string CardNumber, std::string PinCode);
			
			/**
			* @brief Default destructor
			*
			*/
			~Client();
			Client(const Client&) = default;
			Client& operator=(const Client&) = default;
			Client(Client&&) = delete;
			Client& operator=(const Client&&) = delete;

			/**
			* @brief Delete client account
			*
			* @param string account id for deleting
			*/
			void DeleteAccount(const std::string accId);
			/**
			* @brief Create new account
			*
			* @param accType is enum account type
			* @param curType is enum currency type
			*/
			void CreateAccount(const Account::AccountType accType, const Account::CurrencyType curType);
			/**
			* @brief Deposit money on selected account
			*
			* @param accId is account UUID
			* @param amount is amount of money to deposit
			* 
			* @exception std::invalid_argument if depositAmount is negative
			*/
			void DepositOnAccount(const std::string accId, const float amount);
			/**
			* @brief Withdraw money from selected account
			*
			* @param accId is account UUID
			* @param amount is amount of money to deposit
			* 
			* @exception Account::accExceptions::AccountBlocked If account is blocked
			* @exception Account::accExceptions::OverdraftDisabled If there is no enough
		    *        money to withdraw and overdraft is disabled
			* @exception Account::accExceptions::MaxOverdraftNotSetted If there is no enough
		    *        money to withdraw and max overdraft limit is not setted
			* @exception Account::accExceptions::OverdrafedMaxLimit If max overdraft limit is overdrafted
			*/
			void WithdrawFromAccount(const std::string accId, const float amount);

			/**
			* @brief Returns true if some client data is changed
			*
			*/
			bool IsDataChanged() const { return this->changedData; }
			/**
			* @brief Get client name
			*
			* @return string name
			*/
			std::string GetName() const { return this->name; }
			/**
			* @brief Get client address
			*
			* @return string address
			*/
			std::string GetAddress() const { return this->address; }
			/**
			* @brief Get client phone number
			*
			* @return string phone number
			*/
			std::string GetPhoneNumber() const { return this->phoneNumber; }
			/**
			* @brief Get client date of birth
			*
			* @return string date of birth
			*/
			std::string GetDateOfBirth() const { return this->dateOfBirth; }
			/**
			* @brief Get client person identification number
			*
			* @return string person identification number
			*/
			std::string GetPersonIdentifactionNumber() const { return this->personIdentifactionNumber; }
			/**
			* @brief Get client card number
			*
			* @return string card number
			*/
			std::string GetCardNumber() const { return this->cardNumber; }
			/**
			* @brief Get client pin code
			*
			* @return string pin code
			*/
			std::string GetPinCode() const { return this->pinCode; }
			/**
			* @brief Get client total amount
			* 
			* @param cType The type of currency in which you want the total amount to be returned
			* 
			* @return float total amount
			*/
			float GetTotalAmount(Account::CurrencyType cType) const;
			/**
			* @brief Get all clients accounts
			*
			* @return vector Account
			*/
			std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> GetAccounts() const { return this->client_accounts; }
			/**
			* @brief Get account with accId
			*
			* @return Account
			*/
			std::shared_ptr<Account::Account> GetAccount(const std::string accId) const;
			/**
			* @brief Get all clients credits
			*
			* @return vector Credit
			*/
			std::vector<Credit::Credit> GetCredits() const { return this->client_credits; }

			/**
			* @brief Set all clients accounts
			*
			*/
			void SetClientAccounts(std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> ClientAccounts);
	};
}

