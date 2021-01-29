#include "pch.h"
#include "Client.h"
#include "AccountTypeExists.h"
#include "EmptyInitialValues.h"
#include "InvalidValue.h"
#include "InvalidDeleteAccount.h"
#include "ClientDataConstants.h"
#include "CurrencyConversion.h"
#include "UUIDGenerator.h"


Client::Client::Client(IDatabase* DatabaseConector, std::string Name, std::string Address, std::string PhoneNumber,
	 std::string DateOfBirth, std::string PersonIdentificationNumber, std::string CardNumber, std::string PinCode)
	: name(Name), address(Address), phoneNumber(PhoneNumber), dateOfBirth(DateOfBirth),
		personIdentifactionNumber(PersonIdentificationNumber), cardNumber(CardNumber), pinCode(PinCode),
		changedData(false), databaseConnector(DatabaseConector)
{
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

	this->clientId = UUIDGenerator::GetClientUUID();
	this->totalAmount = 0.0f;
	this->client_accounts = std::make_shared<std::vector<std::shared_ptr<Account::Account>>>();
}

Client::Client::~Client()
{
	
}

void Client::Client::DeleteAccount(const std::string accId)
{
	auto account = std::find_if(this->client_accounts->begin(), this->client_accounts->end(),
		[&accId](const std::shared_ptr<Account::Account>& a) { return !a->GetAccountId().compare(accId); });

	if (account != this->client_accounts->end())
	{
		if((*account)->GetBalance() != 0.0f)
			throw clExceptions::InvalidDeleteAccount(this->clientId, accId);

		this->client_accounts->erase(account);
		this->changedData = true;
	}
}

void Client::Client::CreateAccount(const Account::AccountType accType, const Account::CurrencyType curType)
{
	if (std::any_of(this->client_accounts->begin(), this->client_accounts->end(),
		[accType](const std::shared_ptr<Account::Account>& acc) { return acc->GetAccountType() == accType;}))
		throw clExceptions::AccountTypeExists(this->clientId);

	this->client_accounts->push_back(std::make_shared<Account::Account>(accType, curType));
	this->changedData = true;
}

void Client::Client::DepositOnAccount(const std::string accId, const float amount)
{
	auto account = std::find_if(this->client_accounts->begin(), this->client_accounts->end(),
		[&accId](const std::shared_ptr<Account::Account>& a) { return !a->GetAccountId().compare(accId); });

	if (account != this->client_accounts->end())
	{
		(*account)->Deposit(amount);
		this->totalAmount += (amount * Account::ExchangeRateMap[(*account)->GetCurrencyType()]);
		this->changedData = true;
	}
}

void Client::Client::WithdrawFromAccount(const std::string accId, const float amount)
{
	auto account = std::find_if(this->client_accounts->begin(), this->client_accounts->end(),
		[&accId](const std::shared_ptr<Account::Account>& a) { return !a->GetAccountId().compare(accId); });

	if (account != this->client_accounts->end())
	{
		(*account)->Withdraw(amount);
		this->totalAmount -= (amount * Account::ExchangeRateMap[(*account)->GetCurrencyType()]);
		this->changedData = true;
	}
}

float Client::Client::GetTotalAmount(Account::CurrencyType cType) const
{
	return this->totalAmount / Account::ExchangeRateMap[cType];
}

std::shared_ptr<Account::Account> Client::Client::GetAccount(const std::string accId) const
{
	auto account = std::find_if(this->client_accounts->begin(), this->client_accounts->end(),
		[&accId](const std::shared_ptr<Account::Account>& a) { return !a->GetAccountId().compare(accId); });

	if (account != this->client_accounts->end())
	{
		return *account;
	}
}

void Client::Client::SetClientAccounts(std::shared_ptr<std::vector<std::shared_ptr<Account::Account>>> ClientAccounts)
{
	this->client_accounts = ClientAccounts;

	this->totalAmount = 0.0f;

	for (auto acc = this->client_accounts->begin(); acc != this->client_accounts->end(); acc++)
	{
		this->totalAmount += ((*acc)->GetBalance() * Account::ExchangeRateMap[(*acc)->GetCurrencyType()]);
	}
}
