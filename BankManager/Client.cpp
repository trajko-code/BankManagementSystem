#include "pch.h"
#include "Client.h"


Client::Client::Client(std::string Name, std::string Address, std::string PhoneNumber, std::string DateOfBirth,
	 std::string PersonIdentificationNumber, std::string CardNumber, std::string PinCode)
	: name(Name), address(Address), phoneNumber(PhoneNumber), dateOfBirth(DateOfBirth),
		personIdentifactionNumber(PersonIdentificationNumber), cardNumber(CardNumber), pinCode(PinCode)
{
	this->totalAmount = 0.0f;
}

Client::Client::~Client()
{
}

float Client::Client::GetTotalAmount(Account::CurrencyType cType) const
{
	return 0.0f;
}
