#pragma once

#include "pch.h"

namespace Account
{
	namespace accExceptions
	{
		class OverdraftedMaxLimit : public std::exception
		{
			std::string accId;
		public:
			OverdraftedMaxLimit(std::string AccId) : accId(AccId) {};

			const char* what()
			{
				std::string retVal = "Client overdrafted max overdraft limit on account '" + accId + "'and account is blocked!";

				return retVal.c_str();
			}
		};
	}
}