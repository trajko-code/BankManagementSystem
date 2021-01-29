#pragma once

#include "pch.h"
#include "UUIDGenerator.h"


std::string UUIDGenerator::GetNewUUID()
{
	UUID uuid;
	UuidCreate(&uuid);
	char* str;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);

	return std::string(str);
}

std::string UUIDGenerator::GetAccountUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, ACCOUNT_PREFIX_UUID);

	return uuid;
}

std::string UUIDGenerator::GetClientUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, CLIENT_PREFIX_UUID);

	return uuid;
}

std::string UUIDGenerator::GetCreditUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, CREDIT_PREFIX_UUID);

	return uuid;
}