#pragma once

#include "pch.h"
#include "Client.h"
#include "IDatabase.h"

#define CLIENT_MANAGER_API _declspec(dllexport)
#define NUMBER_OF_RECONNECTION 3

namespace Client
{
	class CLIENT_MANAGER_API ClientManager
	{
		private:
			std::shared_ptr<Client> m_client;
			IDatabase* m_databaseConnector;

		public:
			ClientManager(IDatabase* dbConnector);
			~ClientManager();
			ClientManager(const ClientManager&) = delete;
			ClientManager& operator=(const ClientManager&) = delete;
			ClientManager(ClientManager&&) = delete;
			ClientManager& operator=(const ClientManager&&) = delete;

			/**
			* @brief Create new client
			*
			*/
			void AddNewClient(std::string name, std::string address, std::string phoneNumber,
				std::string dateOfBirth, std::string personIdentificationNumber,
				std::string cardNumber, std::string pinCode);
			/**
			* @brief Load client by card number
			*
			*/
			void LoadClient(const std::string cardNumber);
			/**
			* @brief Client authentication by card number and pin code
			* 
			* @return True if client authentication is successful
			*/
			bool AuthenticateClient(const std::string cardNumber, const std::string pinCode);
			/**
			* @brief Updates client data if changed
			*
			*/
			void UpdateClient() const;
			
			/**
			* @brief Delete client account
			*
			* @param string account id for deleting
			*/
			void DeleteClientAccount(const std::string accId);
			/**
			* @brief Create new account
			*
			* @param accType is enum account type
			* @param curType is enum currency type
			*/
			void CreateClientAccount(const Account::AccountType accType, const Account::CurrencyType curType);
			/**
			* @brief Deposit money on selected account
			*
			* @param accId is account UUID
			* @param amount is amount of money to deposit
			*
			* @exception std::invalid_argument if depositAmount is negative
			*/
			void DepositOnClientAccount(const std::string accId, const float amount);
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
			void WithdrawFromClientAccount(const std::string accId, const float amount);

			/**
			* @brief Get client name
			*
			* @return string name
			*/
			std::string GetClientName() const { return this->m_client->GetName(); }
			/**
			* @brief Get client address
			*
			* @return string address
			*/
			std::string GetClientAddress() const { return this->m_client->GetAddress(); }
			/**
			* @brief Get client phone number
			*
			* @return string phone number
			*/
			std::string GetClientPhoneNumber() const { return this->m_client->GetPhoneNumber(); }
			/**
			* @brief Get client date of birth
			*
			* @return string date of birth
			*/
			std::string GeClienttDateOfBirth() const { return this->m_client->GetDateOfBirth(); }
			/**
			* @brief Get client person identification number
			*
			* @return string person identification number
			*/
			std::string GetClientPersonIdentifactionNumber() const { return this->m_client->GetPersonIdentifactionNumber(); }
			/**
			* @brief Get client card number
			*
			* @return string card number
			*/
			std::string GetClientCardNumber() const { return this->m_client->GetCardNumber(); }
			/**
			* @brief Get client pin code
			*
			* @return string pin code
			*/
			std::string GetClientPinCode() const { return this->m_client->GetPinCode(); }
			/**
			* @brief Get client total amount
			*
			* @param cType The type of currency in which you want the total amount to be returned
			*
			* @return float total amount
			*/
			float GetClientTotalAmount(Account::CurrencyType cType) const { return this->m_client->GetTotalAmount(cType); };
			/**
			* @brief Get all clients accounts
			*
			* @return vector Account
			*/
			std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> GetClientAccounts() const { return this->m_client->GetAccounts(); }
			/**
			* @brief Get account with accId
			*
			* @return Account
			*/
			std::shared_ptr<Account::Account> GetClientAccount(const std::string accId) const { return this->m_client->GetAccount(accId); }
			/**
			* @brief Get all clients credits
			*
			* @return vector Credit
			*/
			std::vector<Credit::Credit> GetClientCredits() const { return this->m_client->GetCredits(); }
		
		private:
			void TryToConnect() const;
	};
}