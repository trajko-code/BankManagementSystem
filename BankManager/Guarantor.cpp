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
