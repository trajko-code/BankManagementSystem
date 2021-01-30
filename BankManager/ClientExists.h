#pragma once

#include "pch.h"

namespace Database
{
	namespace dbExceptions
	{
		class ClientExists : public std::exception
		{
		public:
			ClientExists() {}

			const char* what()
			{
				return "Can not add client, because client with this person identification number exists in dabatase.";
			}
		};
	}
}