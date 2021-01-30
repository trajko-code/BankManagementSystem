#pragma once

#include "pch.h"

namespace Database
{
	namespace dbExceptions
	{
		class ClientNotExists : public std::exception
		{
		public:
			ClientNotExists() {}

			const char* what()
			{
				return "Can not load client, because client with this card number doesn't exist in dabatase.";
			}
		};
	}
}