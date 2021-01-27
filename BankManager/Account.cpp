#include "pch.h"
#include "Account.h"


Account::Account::Account(AccountType aType, CurrencyType cType, bool Blocked, bool OverdraftEnabled,
    float MaxOverdraft, float Amount)
    : accType(aType), curType(cType), blocked(Blocked), overdraftEnabled(OverdraftEnabled),
      maxOverdraft(MaxOverdraft), amount(Amount)
{
}

Account::Account::~Account()
{
}
