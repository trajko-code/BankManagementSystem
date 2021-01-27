#include "pch.h"

#include "../BankManager/Account.h"
//#include "../BankManager/Student.h"
#include "../BankManager/IDatabase.h"

class DatabaseConnectorMock : public IDatabase
{
public:
    MOCK_METHOD(bool, Connect, (), (override));
    MOCK_METHOD(bool, Disconnect, (), (override));
    MOCK_METHOD(bool, IsConnected, (), (override));
    MOCK_METHOD(int, Query, (std::string query), (override));
    MOCK_METHOD(std::string, Query, (int query), (override));
};

TEST(Student, TestConnection) {
    ::testing::NiceMock<DatabaseConnectorMock> databaseConnection;
    EXPECT_CALL(databaseConnection, Connect())
        .Times(::testing::AtLeast(1));
    //Student student(&databaseConnection);
}

TEST(TestCaseName, TestName) {
    Account::Account acc;

    EXPECT_EQ(5, acc.Add(2, 3));
}

TEST(NewTest, ImeTesta) {
    EXPECT_EQ(5, 5);
}

TEST(NewTest123, ImeTesta123) {
    EXPECT_EQ(4, 4);
}

