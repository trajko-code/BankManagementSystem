#pragma once

#include "pch.h"

namespace Account
{
	namespace accExceptions
	{
		class AccountBlocked : public std::exception
		{
			std::string accId;
		public:
			AccountBlocked(std::string AccId) : accId(AccId) {};

			const char* what()
			{
				std::string retVal = "Account '" + accId + "' is blocked!";

				return retVal.c_str();
			}
		};
	}
}