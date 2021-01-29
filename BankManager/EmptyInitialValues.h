#pragma once

#include "pch.h"

namespace Client
{
	namespace clExceptions
	{
		class EmptyInitialValues : public std::exception
		{
			std::string clientId;
		public:
			EmptyInitialValues(std::string ClientId) : clientId(ClientId) {}

			const char* what()
			{
				std::string retVal = "Client " + clientId + " has empty initial values.";

				return retVal.c_str();
			}
		};
	}
}
