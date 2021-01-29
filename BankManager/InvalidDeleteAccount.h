#pragma once

#include "pch.h"

namespace Client
{
	namespace clExceptions
	{
		class InvalidDeleteAccount : public std::exception
		{
			std::string clientId;
			std::string accauntInfo;
		public:
			InvalidDeleteAccount(std::string ClientId, std::string AccauntInfo)
				: clientId(ClientId), accauntInfo(AccauntInfo) {}

			const char* what()
			{
				std::string retVal = "Account " + this->accauntInfo + "of client " + clientId + " can not be deleted.";

				return retVal.c_str();
			}
		};
	}
}