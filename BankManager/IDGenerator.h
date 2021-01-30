#pragma once

#include "pch.h"
#include "BankPolicy.h"
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

namespace IDGenerator
{
	std::string _declspec(dllexport) GetNewUUID();

	std::string _declspec(dllexport) GetAccountUUID();
	std::string _declspec(dllexport) GetClientUUID();
	std::string _declspec(dllexport) GetCreditUUID();

	std::string _declspec(dllexport) GetCardNumber();
	std::string _declspec(dllexport) GetPinCode();
}