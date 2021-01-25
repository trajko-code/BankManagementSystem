#include "pch.h"
#include "Student.h"

Student::Student(IDatabase* databaseConnector)
    : m_databaseConnector(databaseConnector)
{
    this->m_databaseConnector->Connect();
}

int Student::QueryIndex(std::string Name)
{
    if (this->m_databaseConnector->IsConnected())
        return this->m_databaseConnector->Query(Name);
    else
        throw std::exception();

}

std::string Student::QueryName(int index)
{
    if (this->m_databaseConnector->IsConnected())
        return this->m_databaseConnector->Query(index);
    else
    {
        this->m_databaseConnector->Connect();

        return this->m_databaseConnector->Query(index);
    }
}

Student::~Student() {
    if (this->m_databaseConnector->IsConnected())
        this->m_databaseConnector->Disconnect();
}