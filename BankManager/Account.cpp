#include "pch.h"
#include "Account.h"

Account::Account::Account(std::string accountId, AccountType aType, CurrencyType cType)
    : accType(aType), curType(cType), blocked(false), overdraftEnabled(false),
      maxOverdraft(0.0f), balance(0.0f)
{
}

Account::Account::~Account()
{
}

void Account::Account::Deposit(float depositAmount)
{
    if (depositAmount < 0.0f)
        throw std::invalid_argument("Negative amount");
    this->balance += depositAmount;
}

void Account::Account::Withdraw(float withdrawAmount)
{
    if (withdrawAmount < 0.0f)
        throw std::invalid_argument("Negative argument!");
    else if (this->blocked)
        throw accExceptions::AccountBlocked(this->GetAccountId());
    
    if (this->balance < withdrawAmount)
    {
        if(!this->IsOverdraftEnabled())
            throw accExceptions::OverdraftDisabled(this->GetAccountId());
        else if (this->maxOverdraft >= 0.0f)
            throw accExceptions::MaxOverdraftNotSetted(this->GetAccountId());
       
        this->balance -= withdrawAmount;

        if (this->balance < this->maxOverdraft)
        {
            this->BlockAccount();
            throw accExceptions::OverdraftedMaxLimit(this->GetAccountId());
        }
    }
    else
        this->balance -= withdrawAmount;
}

void Account::Account::SetAccountType(AccountType aType)
{
    this->accType = aType;
}

void Account::Account::SetMaxOverdraft(float MaxOverdraft)
{
    if (MaxOverdraft > 0.0f)
        this->maxOverdraft = -MaxOverdraft;
    else
        this->maxOverdraft = MaxOverdraft;
}
