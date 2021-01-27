#include "pch.h"
#include "Credit.h"



Credit::Credit::Credit(float Amount, Account::CurrencyType CType, float InterestRate, 
		std::tm BeginDate, std::tm EndDate, int Duration, std::vector<Guarantor> Guarantors)
	:active(true), amount(Amount), curType(CType), interestRate(InterestRate), beginDate(BeginDate),
	endDate(EndDate), duration(Duration), guarantors(Guarantors)
{
}

Credit::Credit::~Credit()
{
}
