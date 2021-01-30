#include "pch.h"
#include "ClientManager.h"
#include "ClientExists.h"
#include "UnableToConnect.h"
#include "ClientNotExists.h"

Client::ClientManager::ClientManager(IDatabase* dbConnector)
	:m_databaseConnector(dbConnector)
{
	this->m_databaseConnector->Connect();
}

Client::ClientManager::~ClientManager()
{
	if (this->m_databaseConnector->IsConnected())
		this->m_databaseConnector->Disconnect();
}

void Client::ClientManager::DeleteClientAccount(const std::string accId)
{
	this->m_client->DeleteAccount(accId);
}

void Client::ClientManager::CreateClientAccount(const Account::AccountType accType, const Account::CurrencyType curType)
{
	this->m_client->CreateAccount(accType, curType);
}

void Client::ClientManager::DepositOnClientAccount(const std::string accId, const float amount)
{
	this->m_client->DepositOnAccount(accId, amount);
}

void Client::ClientManager::WithdrawFromClientAccount(const std::string accId, const float amount)
{
	this->m_client->WithdrawFromAccount(accId, amount);
}

void Client::ClientManager::TryToConnect()
{
	int i = 0;
	while(!this->m_databaseConnector->Connect() && ++i < NUMBER_OF_RECONNECTION) {}

	if (i == NUMBER_OF_RECONNECTION)
		throw Database::dbExceptions::UnableToConnect();
}

void Client::ClientManager::AddNewClient(std::string name, std::string address, std::string phoneNumber,
	std::string dateOfBirth, std::string personIdentificationNumber, std::string cardNumber, std::string pinCode)
{
	if (!this->m_databaseConnector->IsConnected())
		this->TryToConnect();

	if (this->m_databaseConnector->CheckIfClientExists(personIdentificationNumber))
		throw Database::dbExceptions::ClientExists();

	this->m_client = std::make_shared<Client>(name, address, phoneNumber, dateOfBirth, 
		personIdentificationNumber, cardNumber, pinCode);

	this->m_databaseConnector->AddNew(this->m_client);
}

void Client::ClientManager::LoadClient(std::string cardNumber)
{
	if (!this->m_databaseConnector->IsConnected())
		this->TryToConnect();

	this->m_client = this->m_databaseConnector->Load(cardNumber);

	if (!this->m_client)
		throw Database::dbExceptions::ClientNotExists();
}

bool Client::ClientManager::AuthenticateClient(std::string cardNumber, std::string pinCode)
{
	if (!this->m_databaseConnector->IsConnected())
		this->TryToConnect();

	this->m_client = this->m_databaseConnector->Load(cardNumber, pinCode);

	if (this->m_client)
		return true;
	else
		return false;
}

void Client::ClientManager::UpdateClient()
{
	if (!this->m_client->IsDataChanged())
		return;

	if (!this->m_databaseConnector->IsConnected())
		this->TryToConnect();

	this->m_databaseConnector->Update(this->m_client);
}
