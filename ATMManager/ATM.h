#pragma once

#include "IDeployControl.h"
#include "ICreditCardReader.h"
#include "IKeyboard.h"
#include "IDisplay.h"
#include "ATMMessages.h"
#include "ATMState.h"
#include "KeyCodes.h"

namespace ATM
{
	using namespace ManufacturerAPI;

	template <class bankManager>
	class ATM
	{
		private:
			ICreditCardReader* m_cardReader;
			IDeployControl* m_deployControl;
			IDisplay* m_display;
			IKeyboard* m_keyboard;

			bankManager* m_bankManager;

			std::string tmp_cardNumber;
			std::string tmp_accountId;
			std::string tmp_pinCode;
			std::string tmp_amount;
			ATMState tmp_state;
		public:
			ATM(bankManager* bankManager, ICreditCardReader* cardReader,
				IDeployControl* deployControl, IDisplay* display, IKeyboard* keyboard);
			~ATM();
			ATM(const ATM&) = delete;
			ATM& operator=(const ATM&) = delete;
			ATM(ATM&&) = delete;
			ATM& operator=(const ATM&&) = delete;

			int Run();
		private:
			void KeyPressed(KEY_t key);
			void PressedEnter();
			void PressedCancelKey();
			void PressedOption1();
			void PressedOption2();
			void CardInsertedCallback(std::string cardNumber, std::string accountId);
			void EndProcess(std::string message);
	};

	template <class bankManager>
	ATM<bankManager>::ATM(bankManager* bankManager, ICreditCardReader* cardReader,
		IDeployControl* deployControl, IDisplay* display, IKeyboard* keyboard)
		: m_cardReader(cardReader), m_deployControl(deployControl),
		m_display(display), m_keyboard(keyboard), m_bankManager(bankManager),
	    tmp_state(ATMState::Initial)
	{
	}

	template <class bankManager>
	ATM<bankManager>::~ATM()
	{
	}

	template <class bankManager>
	int ATM<bankManager>::Run()
	{
		this->m_display->DisplayText(INSERT_CARD);
		this->m_cardReader->CreditCardInserted(
			[this](std::string cardNumber, std::string accountId) 
			{ return this->CardInsertedCallback(cardNumber, accountId); });
		this->m_display->DisplayText(INSERT_PIN);
		this->tmp_state = ATMState::EnterPin;

		while (this->tmp_state == ATMState::EnterPin)
		{
			this->m_keyboard->KeypadSetOnKeyPressed(
				[this](KEY_t key) { return this->KeyPressed(key); });
		}

		if (this->tmp_state == ATMState::Cancel)
		{
			this->EndProcess(PRESSED_CANCEL);
		}
		else if (this->tmp_state == ATMState::Initial)
		{
			if (!this->m_bankManager->AuthenticateClient(this->tmp_cardNumber, this->tmp_pinCode))
			{
				this->EndProcess(AUTHENTIFICATION_FAILED);
			}
			else
			{
				this->m_display->DisplayText(AUTHENTIFICATION_SUCCESS);
				this->m_display->DisplayText(USER_OPTIONS);
				this->tmp_state = ATMState::SelectingOptions;

				while (this->tmp_state == ATMState::SelectingOptions)
				{
					this->m_keyboard->KeypadSetOnKeyPressed(
						[this](KEY_t key) { return this->KeyPressed(key); });
				}

				if (this->tmp_state == ATMState::Option1)
				{
					this->m_display->DisplayText(OPTION1);

					auto acc = this->m_bankManager->GetClientAccount(this->tmp_accountId);
					this->EndProcess(std::to_string(acc->GetBalance()));
				}
				else if(this->tmp_state == ATMState::Option2)
				{
					this->m_display->DisplayText(OPTION2);

					this->tmp_state = ATMState::EnterAmount;

					while (this->tmp_state == ATMState::EnterAmount)
					{
						this->m_keyboard->KeypadSetOnKeyPressed(
							[this](KEY_t key) { return this->KeyPressed(key); });
					}

					if (this->tmp_state == ATMState::Cancel)
					{
						this->EndProcess(PRESSED_CANCEL);
					}
					else if (this->tmp_state == ATMState::Initial)
					{
						this->m_deployControl->DeployCash(std::stof(this->tmp_amount));
						
						if (this->m_deployControl->IsCashDeployed())
						{
							this->m_bankManager->WithdrawFromClientAccount(
								this->tmp_accountId, std::stof(this->tmp_amount));

							this->EndProcess(WITHDRAW_SUCCESS);
						}
						else
						{
							this->EndProcess(WITHDRAW_FAILURE);
						}
					}
				}
				else if (this->tmp_state == ATMState::Cancel)
				{
					this->EndProcess(PRESSED_CANCEL);
				}
			}
		}

		return 0;
	}

	template <class bankManager>
	void ATM<bankManager>::KeyPressed(KEY_t key)
	{
		switch (key)
		{
			case KEY_t::Zero:
			case KEY_t::One:
			case KEY_t::Two:
			case KEY_t::Three:
			case KEY_t::Four:
			case KEY_t::Five:
			case KEY_t::Six:
			case KEY_t::Seven:
			case KEY_t::Eight:
			case KEY_t::Nine:
				if (this->tmp_state == ATMState::EnterPin)
					this->tmp_pinCode += std::to_string(key);
				else if (this->tmp_state == ATMState::EnterAmount)
					this->tmp_amount += std::to_string(key);
				break;
			case KEY_t::Enter:
				this->PressedEnter();
				break;
			case KEY_t::Cancel:
				this->PressedCancelKey();
				break;
			case KEY_t::Option1:
				this->PressedOption1();
				break;
			case KEY_t::Option2:
				this->PressedOption2();
				break;
			default:
				break;
		}
	}

	template<class bankManager>
	inline void ATM<bankManager>::PressedEnter()
	{
		if (this->tmp_state == ATMState::EnterPin || this->tmp_state == ATMState::EnterAmount)
			this->tmp_state = ATMState::Initial;
	}

	template<class bankManager>
	inline void ATM<bankManager>::PressedCancelKey()
	{
		this->tmp_state = ATMState::Cancel;
	}

	template<class bankManager>
	inline void ATM<bankManager>::PressedOption1()
	{
		if (this->tmp_state == ATMState::SelectingOptions)
			this->tmp_state = ATMState::Option1;
	}

	template<class bankManager>
	inline void ATM<bankManager>::PressedOption2()
	{
		if (this->tmp_state == ATMState::SelectingOptions)
			this->tmp_state = ATMState::Option2;
	}

	template <class bankManager>
	void ATM<bankManager>::CardInsertedCallback(std::string cardNumber, std::string accountId)
	{
		this->tmp_cardNumber = cardNumber;
		this->tmp_accountId = accountId;
	}
	template<class bankManager>
	inline void ATM<bankManager>::EndProcess(std::string message)
	{
		this->tmp_accountId.clear();
		this->tmp_cardNumber.clear();
		this->tmp_pinCode.clear();
		this->tmp_amount.clear();
		this->tmp_state = ATMState::Initial;

		this->m_display->DisplayText(message);
		this->m_cardReader->EjectCreditCard();
	}
}