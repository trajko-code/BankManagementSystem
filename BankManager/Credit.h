#pragma once

#define CREDIT_API _declspec(dllexport)

#include "pch.h"
#include "Guarantor.h"
#include "CurrencyType.h"
#include <ctime>

namespace Credit
{
	class CREDIT_API Credit
	{
		private:
			bool active;
			float amount;
			Account::CurrencyType curType;
			float interestRate;
			struct std::tm beginDate;
			struct std::tm endDate;
			int duration;
			float monthlyPayment;
			std::vector<std::unique_ptr<Guarantor>> guarantors;

		public:
			/**
			 * @brief Default contstructor
			 *
			 */
			Credit(float Amount, Account::CurrencyType CType, float InterestRate,
				struct std::tm BeginDate, struct std::tm EndDate, int Duration,
				std::unique_ptr<std::vector<std::unique_ptr<Guarantor>>> Guarantors);
			
			/**
			* @brief Default destructor
			*
			*/
			~Credit();
			Credit(const Credit&) = delete;
			Credit& operator=(const Credit&) = delete;
			Credit(Credit&&) = delete;
			Credit& operator=(const Credit&&) = delete;


			/**
			* @brief Checks if credit is active
			*
			* @return bool active
			*/
			bool IsActive() const { return this->active; }
			/**
			* @brief Get credit amount
			*
			* @return float amount
			*/
			float GetAmount() const { return this->amount; }
			/**
			* @brief Get credit currency type
			*
			* @return Account::CurrencyType curType
			*/
			Account::CurrencyType GetCurrencyType() const { return this->curType; }
			/**
			* @brief Get credit interest rate
			*
			* @return float interestRate
			*/
			float GetInterestRate() const { return this->interestRate; }
			/**
			* @brief Get credit begin date
			*
			* @return struct std::tm beginDate
			*/
			struct std::tm GetBeginDate() const { return this->beginDate; }
			/**
			* @brief Get credit end date
			*
			* @return struct std::tm endDate
			*/
			struct std::tm GetEndDate() const { return this->endDate; }
			/**
			* @brief Get credit duration in months
			*
			* @return int duration
			*/
			int GetDuration() const { return this->duration; }
			/**
			* @brief Get credit monthly payment
			*
			* @return float monthlyPayment
			*/
			float GetMonthlyPayment() const { return this->monthlyPayment; }
			/**
			* @brief Get credit guarantors
			*
			* @return std::vector<std::unique_ptr<Guarantor>> guarantors
			*/
			std::vector<std::unique_ptr<Guarantor>> GetGuarantors(Account::CurrencyType cType) const { return this->guarantors; };

	};
}


