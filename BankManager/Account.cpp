#include "pch.h"
#include "Account.h"


Account::Account::Account(AccountType aType, CurrencyType cType)
    : accType(aType), curType(cType), blocked(false), overdraftEnabled(false),
      maxOverdraft(0.0f), balance(0.0f)
{
}

Account::Account::~Account()
{
}

bool Account::Account::Deposit(float depositAmount)
{
    if (depositAmount < 0.0f)
        return false;
        //throw std::invalid_argument("Negative amount");
    this->balance += depositAmount;
    return true;
}

bool Account::Account::Withdraw(float withdrawAmount)
{
    return false;
}
