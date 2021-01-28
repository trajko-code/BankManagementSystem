#include "pch.h"
#include "Client.h"
#include "EmptyInitialValues.h"
#include "InvalidValue.h"
#include "ClientDataConstants.h"


Client::Client::Client(IDatabase* DatabaseConector, std::string Name, std::string Address, std::string PhoneNumber,
	 std::string DateOfBirth, std::string PersonIdentificationNumber, std::string CardNumber, std::string PinCode)
	: name(Name), address(Address), phoneNumber(PhoneNumber), dateOfBirth(DateOfBirth),
		personIdentifactionNumber(PersonIdentificationNumber), cardNumber(CardNumber), pinCode(PinCode),
		changedData(false), databaseConnector(DatabaseConector)
{
	this->totalAmount = 0.0f;
	if (Name.empty() || Address.empty() || PhoneNumber.empty() || DateOfBirth.empty()
		|| PersonIdentificationNumber.empty() || CardNumber.empty() || PinCode.empty())
		throw clExceptions::EmptyInitialValues(this->clientId);

	int personIdNumberLength = PERSON_ID_NUMBER_LENGTH;
	if (PersonIdentificationNumber.length() != personIdNumberLength)
		throw clExceptions::InvalidValue(this->clientId, "invalid length of person identification number");
	int CardNumberLength = CARD_NUMBER_LENGTH;
	if (CardNumber.length() != CardNumberLength)
		throw clExceptions::InvalidValue(this->clientId, "invalid length of card number");
	int pinCodeLength =PIN_CODE_LENGTH;
	if (PinCode.length() != pinCodeLength)
		throw clExceptions::InvalidValue(this->clientId, "invalid length of pin code");
}

Client::Client::~Client()
{
	
}

float Client::Client::GetTotalAmount(Account::CurrencyType cType) const
{
	return 0.0f;
}
