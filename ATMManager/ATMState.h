#pragma once

#pragma once

namespace ATM
{
	enum class ATMState
	{
		Initial,
		Cancel,
		EnterPin,
		EnterAmount,
		SelectingOptions,
		Option1,
		Option2
	};
}