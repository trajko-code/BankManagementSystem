#pragma once

#include <string>
#include <functional>

namespace ManufacturerAPI
{
	class ICreditCardReader {
		public:
			virtual void CreditCardInserted(std::function<void(std::string cardNumber, std::string accountId)> cbFunciton) = 0;
			virtual void EjectCreditCard() = 0;
		private:
	};
}