#pragma once

//#ifdef DATABASE_EXPORTS
#define DATABASE_API _declspec(dllexport)
//#else
//#define DATABASE_API _declspec(dllimport)
//#endif

#include <string>
#include "Client.h"

class DATABASE_API IDatabase {
    public:
        virtual bool Connect() = 0;
        virtual bool Disconnect() = 0;
        virtual bool IsConnected() = 0;

        virtual void AddNew(std::shared_ptr<Client::Client> client) = 0;
        virtual void Update(std::shared_ptr<Client::Client> client) = 0;
        virtual void UpdateClientAccount(std::shared_ptr<Client::Client> client, std::string accId) = 0;
        virtual bool CheckIfClientExists(const std::string persionIdentificationNumber) = 0;

        virtual std::shared_ptr<Client::Client> Load(std::string cardNumber, std::string pinCode) = 0;
        virtual std::shared_ptr<Client::Client> Load(std::string cardNumber) = 0;
    private:
};

