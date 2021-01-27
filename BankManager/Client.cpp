#include "pch.h"
#include "Client.h"

Client::Client::Client(std::string Name, std::string Address, std::string DateOfBirth, std::string PinCode)
{
	this->name = Name;
	this->address = Address;
	this->dateOfBirth = DateOfBirth;
	this->pinCode = PinCode;
}

Client::Client::~Client()
{
}
