#pragma once

namespace Credit
{
	class Guarantor
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
			Guarantor(const Guarantor&);
			Guarantor& operator=(const Guarantor&);
			Guarantor(Guarantor&&) = delete;
			Guarantor& operator=(const Guarantor&&) = delete;

			std::string GetName() const { return this->name; }
			std::string GetAddress() const { return this->address; }
			std::string GetPhoneNumber() const { return this->phoneNumber; }
			std::string GetMmonthlyIncome() const { return this->monthlyIncome; }
	};
}
