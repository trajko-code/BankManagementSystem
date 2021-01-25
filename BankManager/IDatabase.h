#pragma once

//#ifdef DATABASE_EXPORTS
#define DATABASE_API _declspec(dllexport)
//#else
//#define DATABASE_API _declspec(dllimport)
//#endif

#include <string>

class DATABASE_API IDatabase {
    public:
        virtual bool Connect() = 0;
        virtual bool Disconnect() = 0;
        virtual bool IsConnected() = 0;
        virtual int Query(std::string query) = 0;
        virtual std::string Query(int query) = 0;
    private:
};

