#pragma once

#include "pch.h"

namespace Client
{
	namespace clExceptions
	{
		class InvalidValue : public std::exception
		{
			std::string clientId;
			std::string exceptionInfo;
		public:
			InvalidValue(std::string ClientId, std::string ExceptionInfo)
				: clientId(ClientId), exceptionInfo(ExceptionInfo) {}

			const char* what()
			{
				std::string retVal = "Client" + clientId + "has" + this->exceptionInfo;

				return retVal.c_str();
			}
		};
	}
}