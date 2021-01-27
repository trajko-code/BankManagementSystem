#pragma once

#define CLIENT_API _declspec(dllexport)

#include "pch.h"
#include "Account.h"
#include "Credit.h"

namespace Client
{
	class CLIENT_API Client
	{
		private:
			std::string clientId;
			std::string name;
			std::string address;
			std::string phoneNumber;
			std::string dateOfBirth;
			std::string personIdentifactionNumber;
			std::string cardNumber;
			std::string pinCode;
			float totalAmount;
			std::vector<Account::Account> client_accounts;
			std::vector<Credit::Credit> client_credits;

		public:
			/**
			 * @brief Default contstructor
			 *
			 */
			Client(std::string Name, std::string Address, std::string DateOfBirth, std::string PinCode);
			
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
			std::string GetName() { return this->name; }
			/**
			* @brief Get all clients accounts
			*
			* @return vector Account
			*/
			std::vector<Account::Account> GetAccounts() { return this->client_accounts; }
			/**
			* @brief Get all clients credits
			*
			* @return vector Credit
			*/
			std::vector<Credit::Credit> GetCredits() { return this->client_credits; }

	};
}

