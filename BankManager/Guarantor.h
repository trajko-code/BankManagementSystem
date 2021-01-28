#pragma once

#define GUARANTOR_API _declspec(dllexport)

namespace Credit
{
	class GUARANTOR_API Guarantor
	{
		private:
			std::string name;
			std::string address;
			std::string phoneNumber;
			std::string monthlyIncome;

		public:
			Guarantor(std::string Name, std::string Address,
				std::string PhoneNumber, std::string MonthlyIncome);
			~Guarantor();
			Guarantor(const Guarantor&) = default;
			Guarantor& operator=(const Guarantor&) = default;
			Guarantor(Guarantor&&) = delete;
			Guarantor& operator=(const Guarantor&&) = delete;

			std::string GetName() const { return this->name; }
			std::string GetAddress() const { return this->address; }
			std::string GetPhoneNumber() const { return this->phoneNumber; }
			std::string GetMmonthlyIncome() const { return this->monthlyIncome; }
	};
}
