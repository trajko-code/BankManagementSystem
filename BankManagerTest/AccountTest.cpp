#include "pch.h"

#include "../BankManager/Account.h"
#include "../BankManager/AccountBlocked.h"
#include "../BankManager/OverdraftDisabled.h"
#include "../BankManager/OverdraftedMaxLimit.h"
#include "../BankManager/MaxOverdraftNotSetted.h"
#include "../BankManager/CurrencyType.h"

namespace AccountTesting
{
    class AccountTest : public ::testing::Test {
        protected:
            void SetUp() override
            {
                acc_ = std::unique_ptr<Account::Account>(new Account::Account(
                   Account::AccountType::DomesticChecking, Account::CurrencyType::Rsd));
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
        ASSERT_THROW(acc_->Deposit(addDeposit), std::invalid_argument);
    }
    
    TEST_F(AccountTest, DepositZero) {
        float addDeposit = 0.0f;
        float firstBalance = acc_->GetBalance();
        acc_->Deposit(addDeposit);
        float secondBalance = acc_->GetBalance();
        ASSERT_EQ(firstBalance, secondBalance);
    }
    
    TEST_F(AccountTest, WithdrawPositive) {
        float addAmount = 100.0f;
        acc_->Deposit(addAmount);
        float balance = acc_->GetBalance();
        ASSERT_EQ(balance, addAmount);

        float withdrawAmount = 50.0f;
        acc_->Withdraw(withdrawAmount);
        ASSERT_EQ(acc_->GetBalance(), balance - withdrawAmount);
    }

    TEST_F(AccountTest, WithdrawPositiveButBlocked) {
        float withdrawAmount = 50.0f;
        float balanceBefore = acc_->GetBalance();
        acc_->BlockAccount();
        ASSERT_THROW(acc_->Withdraw(withdrawAmount), Account::accExceptions::AccountBlocked);
        ASSERT_EQ(balanceBefore, acc_->GetBalance());
    }

    TEST_F(AccountTest, WithdrawNegative) {
        float amount = -50.0f;
        ASSERT_THROW(acc_->Withdraw(amount), std::invalid_argument);
    }

    TEST_F(AccountTest, WithdrawWithOverdraftEnabled) {
        float addAmount = 200.0f;
        acc_->Deposit(addAmount);
        float balanceBefore = acc_->GetBalance();
        
        acc_->EnableOverdraft();
        acc_->SetMaxOverdraft(1000.0f);

        float withdrawAmount = 500.0f;
        acc_->Withdraw(withdrawAmount);
        ASSERT_EQ(balanceBefore - withdrawAmount, acc_->GetBalance());
        ASSERT_LT(acc_->GetBalance(), 0.0f);
    }

    TEST_F(AccountTest, WithdrawWithOverdraftDisabled) {
        float addAmount = 200.0f;
        acc_->Deposit(addAmount);
        float balanceBefore = acc_->GetBalance();

        acc_->DisableOverdraft();

        float withdrawAmount = 500.0f;
        ASSERT_THROW(acc_->Withdraw(withdrawAmount), Account::accExceptions::OverdraftDisabled);
        ASSERT_EQ(balanceBefore, acc_->GetBalance());
    }
    
    TEST_F(AccountTest, WithdrawWithOverdraftDisabledEdgeCase) {
        float addAmount = 50.0f;
        acc_->Deposit(addAmount);
        acc_->DisableOverdraft();
        float getAmount = 50.00001f;
        ASSERT_THROW(acc_->Withdraw(getAmount), Account::accExceptions::OverdraftDisabled);
    }
    
    TEST_F(AccountTest, WithdrawWithOverdraftNotSettedMax) {
        float addAmount = 200.0f;
        acc_->Deposit(addAmount);
        float beginBalance = acc_->GetBalance();

        acc_->EnableOverdraft();

        float getAmount = 500.0f;
        ASSERT_THROW(acc_->Withdraw(getAmount), Account::accExceptions::MaxOverdraftNotSetted);
        ASSERT_EQ(beginBalance, acc_->GetBalance());
    }

    TEST_F(AccountTest, WithdrawWithOverdraftredMaxLimit) {
        float addAmount = 200.0f;
        acc_->Deposit(addAmount);
        float beginBalance = acc_->GetBalance();

        acc_->EnableOverdraft();
        acc_->SetMaxOverdraft(200.0f);

        float getAmount = 500.0f;
        ASSERT_THROW(acc_->Withdraw(getAmount), Account::accExceptions::OverdraftedMaxLimit);
        ASSERT_TRUE(acc_->IsBlocked());
        ASSERT_EQ(beginBalance - getAmount, acc_->GetBalance());
    }

    TEST_F(AccountTest, SetMaxOverdraft)
    {
        float maxLimit = 500.0f;

        acc_->SetMaxOverdraft(maxLimit);
        EXPECT_EQ(-500.0f, acc_->GetMaxOverdraft());

        float negativeMaxLimit = -200.0f;
        acc_->SetMaxOverdraft(negativeMaxLimit);
        EXPECT_EQ(negativeMaxLimit, acc_->GetMaxOverdraft());
    }
}
