#pragma once

#include "pch.h"
#include "IDGenerator.h"
#include "BankPolicy.h"


std::string IDGenerator::GetNewUUID()
{
	UUID uuid;
	UuidCreate(&uuid);
	char* str;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);

	return std::string(str);
}

std::string IDGenerator::GetAccountUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, ACCOUNT_PREFIX_UUID);

	return uuid;
}

std::string IDGenerator::GetClientUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, CLIENT_PREFIX_UUID);

	return uuid;
}

std::string IDGenerator::GetCreditUUID()
{
	std::string uuid = GetNewUUID();
	uuid.insert(0, CREDIT_PREFIX_UUID);

	return uuid;
}

std::string IDGenerator::GetCardNumber()
{
	std::string cardNumber;
	
	while (cardNumber.size() < SIZE_OF_CARD_NUMBER)
	{
		std::string generatedUUID = GetNewUUID();
		int i = 0;

		while (cardNumber.size() < SIZE_OF_CARD_NUMBER && i < generatedUUID.size())
		{
			if (isdigit(generatedUUID[i]))
				cardNumber += generatedUUID[i];
			i++;
		}
	}

	return cardNumber;
}

std::string IDGenerator::GetPinCode()
{
	std::string pinCode;

	while (pinCode.size() < SIZE_OF_PIN_CODE)
	{
		std::string generatedUUID = GetNewUUID();
		int i = 0;

		while (pinCode.size() < SIZE_OF_PIN_CODE && i < generatedUUID.size())
		{
			if (isdigit(generatedUUID[i]))
				pinCode += generatedUUID[i];
			i++;
		}
	}

	return pinCode;
}
