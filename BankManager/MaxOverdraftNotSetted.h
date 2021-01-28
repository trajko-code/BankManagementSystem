#pragma once

#include "pch.h"

namespace Account
{
	namespace accExceptions
	{
		class MaxOverdraftNotSetted : public std::exception
		{
			std::string accId;
		public:
			MaxOverdraftNotSetted(std::string AccId) : accId(AccId) {};

			const char* what()
			{
				std::string retVal = "For account '" + accId + "' max overdraft is not setted!";

				return retVal.c_str();
			}
		};
	}
}