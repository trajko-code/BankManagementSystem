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
			int Add(int a, int b);
	};
}
