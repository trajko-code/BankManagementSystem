#include "pch.h"

#include "../BankManager/Account.h"

namespace AccountTesting
{
    class AccountTest : public ::testing::Test {
        protected:
            void SetUp() override
            {
                acc_ = std::unique_ptr<Account::Account>(
                        new Account::Account(Account::AccountType::DomesticChecking, 
                                Account::CurrencyType::Rsd));
            }

            void TearDown() override
            {
            }

            std::unique_ptr<Account::Account> acc_;
    };

    TEST_F(AccountTest, TestInitialValues) {
        EXPECT_FLOAT_EQ(0.0f, acc_->GetBalance());
        EXPECT_FALSE(acc_->IsBlocked());
        EXPECT_FALSE(acc_->IsOverdraftEnabled());
        EXPECT_FLOAT_EQ(0.0f, acc_->GetMaxOverdraft());
    }
    
    TEST_F(AccountTest, DepositPositive) {
        float addDeposit = 50.0f;
        acc_->Deposit(addDeposit);
        float balance = acc_->GetBalance();
        ASSERT_EQ(balance, addDeposit);
    }
    
    TEST_F(AccountTest, DepositNegative) {
        float addDeposit = -50.0f;
        //ASSERT_THROW(acc_->Deposit(addDeposit), std::invalid_argument);
        float balance = acc_->GetBalance();
        EXPECT_FALSE(acc_->Deposit(addDeposit));
        float newBalance = acc_->GetBalance();
        ASSERT_FLOAT_EQ(balance, newBalance);
    }
    
    TEST_F(AccountTest, DepositZero) {
        float addDeposit = 0.0f;
        float firstBalance = acc_->GetBalance();
        acc_->Deposit(addDeposit);
        float secondBalance = acc_->GetBalance();
        ASSERT_EQ(firstBalance, secondBalance);
    }
    
    /*TEST_F(AccountTest, WithdrawPositiveNotEnough) {
        User::Account a;
        float amount = 50.0f;
        ASSERT_THROW(a.Withdraw(amount), std::out_of_range);
    }*/
    
    //TEST(AccountTest, WithdrawPositiveAddGetNotEnough) {
    //    User::Account a;
    //    float addAmount = 50.0f;
    //    a.Deposit(addAmount);
    //    float getAmount = 100.f;
    //    ASSERT_THROW(a.Withdraw(getAmount), std::out_of_range);
    //}
    //
    //TEST(AccountTest, WithdrawPositiveAddGetEdgeCase) {
    //    User::Account a;
    //    float addAmount = 50.0f;
    //    a.Deposit(addAmount);
    //    float getAmount = 50.0001f;
    //    ASSERT_THROW(a.Withdraw(getAmount), std::out_of_range);
    //}
    //
    //TEST(AccountTest, WithDraw) {
    //    User::Account a;
    //    a.Deposit(100.0f);
    //    a.Withdraw(50.0f);
    //    float balance = a.Balance();
    //    ASSERT_EQ(balance, 50.0f);
    //}
    //
    //TEST(AccountTest, WithDrawNegative) {
    //    User::Account a;
    //    a.Deposit(100.0f);
    //    ASSERT_THROW(a.Withdraw(-50.0f), std::invalid_argument);
    //}
}
