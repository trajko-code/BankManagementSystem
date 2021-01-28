#pragma once

#define CLIENT_API _declspec(dllexport)

#include "pch.h"
#include "Account.h"
#include "Credit.h"
#include "IDatabase.h"

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
			std::vector<Account::Account> client_accounts;
			std::vector<Credit::Credit> client_credits;

		private:
			bool changedData;
			IDatabase* databaseConnector;

		public:
			/**
			 * @brief Default contstructor
			 *
			 */
			Client(IDatabase* DatabaseConector, std::string Name, std::string Address, 
					std::string PhoneNumber, std::string DateOfBirth, std::string PersonIdentificationNumber, 
					std::string CardNumber, std::string PinCode);
			
			/**
			* @brief Default destructor
			*
			*/
			~Client();
			Client(const Client&) = delete;
			Client& operator=(const Client&) = delete;
			Client(Client&&) = delete;
			Client& operator=(const Client&&) = delete;


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
			std::vector<Account::Account> GetAccounts() const { return this->client_accounts; }
			/**
			* @brief Get all clients credits
			*
			* @return vector Credit
			*/
			std::vector<Credit::Credit> GetCredits() const { return this->client_credits; }

	};
}

