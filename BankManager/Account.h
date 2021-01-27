#pragma once

//#ifdef ACCOUNT_EXPORTS
#define ACCOUNT_API _declspec(dllexport)
//#else
//#define ACCOUNT_API _declspec(dllimport)
//#endif // ACCOUNT_EXPORTS

#include "AccountType.h"
#include "CurrencyType.h"

namespace Account
{
	class ACCOUNT_API Account
	{
		private: 
			AccountType accType;
			CurrencyType curType;
			bool blocked;
			bool overdraftEnabled;
			float maxOverdraft;
			float amount;

		public:
			/**
			 * @brief Default contstructor
			 *
			 */
			Account(AccountType aType, CurrencyType cType, bool Blocked, bool OverdraftEnabled, 
				float MaxOverdraft, float Amount);

			/**
			* @brief Default destructor
			*
			*/
			~Account();
			Account(const Account&) = delete;
			Account& operator=(const Account&) = delete;
			Account(Account&&) = delete;
			Account& operator=(const Account&&) = delete;

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
			* @return float amount of money
			*/
			float GetAmount() const { return this->amount; }

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
			void SetAccountType(AccountType aType) { this->accType = aType; }
			/**
			 * @brief Set currency type
			 *
			 * @param cType type of account to be setted
			 */
			void SetCurrencyType(CurrencyType cType) { this->curType = cType; }
			/**
			 * @brief Set maximum allowed overdraft
			 *
			 * @param MaxOverdraft amount of maximum allowed overdraft
			 */
			void SetMaxOverdraft(float MaxOverdraft) { this->maxOverdraft = MaxOverdraft; }

	};
}
