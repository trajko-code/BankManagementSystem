#pragma once

#include "pch.h"
#include "CurrencyType.h"

namespace Account
{
	std::unordered_map<CurrencyType, float> ExchangeRateMap =
	{
		{ CurrencyType::Rsd, 1.0 },
		{ CurrencyType::Eur, 117.670 },
		{ CurrencyType::Usd, 97.0407 },
		{ CurrencyType::Gbp, 133.206 },
		{ CurrencyType::Chf, 109.258 }
	};
}