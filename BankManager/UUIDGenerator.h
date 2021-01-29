#pragma once

#include "pch.h"
//#include <rpcdce.h>
#include "BankPolicy.h"
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

namespace UUIDGenerator
{
	std::string _declspec(dllexport) GetNewUUID();

	std::string _declspec(dllexport) GetAccountUUID();
	std::string _declspec(dllexport) GetClientUUID();
	std::string _declspec(dllexport) GetCreditUUID();
}