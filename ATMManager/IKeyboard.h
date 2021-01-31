#pragma once

#include "KeyCodes.h"

namespace ManufacturerAPI
{
	class IKeyboard {
		public:
			virtual void KeypadSetOnKeyPressed(std::function<void(ATM::KEY_t)> keyPressCallback) = 0;
		private:
	};
}