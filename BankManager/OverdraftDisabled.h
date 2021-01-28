#pragma once

#include "pch.h"

namespace Account
{
	namespace accExceptions
	{
		class OverdraftDisabled : public std::exception
		{
			std::string accId;
		public:
			OverdraftDisabled(std::string AccId) : accId(AccId) {};

			const char* what()
			{
				std::string retVal = "For account '" + accId + "' overdraft is disabled!";

				return retVal.c_str();
			}
		};
	}
}