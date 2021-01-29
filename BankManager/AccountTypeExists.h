#pragma once

#include "pch.h"

namespace Client
{
	namespace clExceptions
	{
		class AccountTypeExists : public std::exception
		{
			std::string clientId;
		public:
			AccountTypeExists(std::string ClientId) : clientId(ClientId) {}

			const char* what()
			{
				std::string retVal = "Client " + clientId + " has account of selected type.";

				return retVal.c_str();
			}
		};
	}
}
