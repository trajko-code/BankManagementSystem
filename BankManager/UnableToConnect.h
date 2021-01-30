#pragma once

#include "pch.h"

namespace Database
{
	namespace dbExceptions
	{
		class UnableToConnect : public std::exception
		{
			public:
				UnableToConnect() {}

				const char* what()
				{
					return "Unable to connect to database.";
				}
		};
	}
}