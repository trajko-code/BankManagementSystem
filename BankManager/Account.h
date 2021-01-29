#pragma once

//#ifdef ACCOUNT_EXPORTS
#define ACCOUNT_API _declspec(dllexport)
//#else
//#define ACCOUNT_API _declspec(dllimport)
//#endif // ACCOUNT_EXPORTS

#include "pch.h"
#include "AccountType.h"
#include "CurrencyType.h"
#include "AccountBlocked.h"
#include "OverdraftDisabled.h"
#include "OverdraftedMaxLimit.h"
#include "MaxOverdraftNotSetted.h"

namespace Account
{
	class ACCOUNT_API Account
	{
		private:
			std::string accountId;
			AccountType accType;
			CurrencyType curType;
			bool blocked;
			bool overdraftEnabled;
			float maxOverdraft;
			float balance;

		public:
			/**
			 * @brief Default contstructor
			 *
			 */
			Account(AccountType aType, CurrencyType cType);

			/**
			* @brief Default destructor
			*
			*/
			~Account();
			Account(const Account&) = default;
			Account& operator=(const Account&) = default;
			//Account(Account&&) = delete;
			//Account& operator=(const Account&&) = delete;

			/**
			* @brief This is the function used to deposit money to the balance
			* 
			* @param depositAmount Amount of monet to deposit
			* 
			* @exception std::invalid_argument if depositAmount is negative
			*/
			void Deposit(float depositAmount);
			/**
			 * @brief This is the function used to withdraw money from the balance.
			 *	
			 * @param withdrawAmount Amount of money to withdraw
			 * 
			 * @exception Account::accExceptions::AccountBlocked If account is blocked
			 * @exception Account::accExceptions::OverdraftDisabled If there is no enough
		     *        money to withdraw and overdraft is disabled
			 * @exception Account::accExceptions::MaxOverdraftNotSetted If there is no enough
		     *        money to withdraw and max overdraft limit is not setted
			 * @exception Account::accExceptions::OverdrafedMaxLimit If max overdraft limit is overdrafted
			 */
			void Withdraw(float withdrawAmount);

			/**
			* @brief Check account blocked
			*
			* @return true if account is blocked, otherwise false
			*/
			bool IsBlocked() const { return this->blocked; }
			/**
			* @brief Check overdraft enabled
			*
			* @return true if overdraft is enabled, otherwise false
			*/
			bool IsOverdraftEnabled() const { return this->overdraftEnabled; }

			/**
			* @brief Get account id
			*
			* @return string accountId
			*/
			std::string GetAccountId() const { return this->accountId; }
			/**
			* @brief Get account type
			*
			* @return AccountType enumeration whose value can be DomesticChecking, ForeignChecking, Savings or CertificateOfDeposit
			*/
			AccountType GetAccountType() const { return this->accType;  }
			/**
			* @brief Get currency type
			*
			* @return CurrencyType enumeration whose value can be Rsd, Eur, Usd, Gbp or Chf
			*/
			CurrencyType GetCurrencyType() const { return this->curType;  }
			/**
			* @brief Get maximum allowed overdraft
			*
			* @return float maximum allowed overdraft
			*/
			float GetMaxOverdraft() const { return this->maxOverdraft; }
			/**
			* @brief Get the total amount of money in the account
			*
			* @return float balance
			*/
			float GetBalance() const { return this->balance; }

			/**
			 * @brief Block account
			 *
			 */
			void BlockAccount() { this->blocked = true; }
			/**
			 * @brief Unblock account
			 *
			 */
			void UnblockAccount() { this->blocked = false; }
			/**
			 * @brief Enable overdraft
			 *
			 */
			void EnableOverdraft() { this->overdraftEnabled = true; }
			/**
			 * @brief Disable overdraft
			 *
			 */
			void DisableOverdraft() { this->overdraftEnabled = false; }

			/**
			 * @brief Set account type
			 *
			 * @param aType type of account to be setted
			 */
			void SetAccountType(AccountType aType);
			/**
			 * @brief Set maximum allowed overdraft
			 *
			 * @param MaxOverdraft amount of maximum allowed overdraft
			 */
			void SetMaxOverdraft(float MaxOverdraft);

	};
}
