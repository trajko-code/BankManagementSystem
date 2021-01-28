#include "pch.h"
#include "Guarantor.h"

Credit::Guarantor::Guarantor(std::string Name, std::string Address, 
	std::string PhoneNumber, std::string MonthlyIncome)
	: name(Name), address(Address), phoneNumber(PhoneNumber), 
	monthlyIncome(MonthlyIncome)
{
}

Credit::Guarantor::~Guarantor()
{
}

//
//Credit::Guarantor::Guarantor(const Guarantor& guarantor)
//{
//	this->name = guarantor.GetName();
//	this->address = guarantor.GetAddress();
//	this->phoneNumber = guarantor.GetPhoneNumber();
//	this->monthlyIncome = guarantor.GetMmonthlyIncome();
//}
//
//Credit::Guarantor& Credit::Guarantor::operator=(const Guarantor& guarantor)
//{
//	Guarantor newGuarantor(guarantor);
//	return newGuarantor;
//}
