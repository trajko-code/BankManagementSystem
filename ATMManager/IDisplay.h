#pragma once

#include <string>

namespace ManufacturerAPI
{
	class IDisplay {
		public:
			virtual void DisplayText(const std::string text_to_display) = 0;
		private:
	};
}