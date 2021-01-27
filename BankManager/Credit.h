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
			std::vector<Guarantor> guarantors;


	};
}


