#pragma once

namespace ManufacturerAPI
{
	class IDeployControl {
		public:
			virtual void DeployCash(int deployAmount) = 0;
			virtual bool IsCashDeployed() = 0;
		private:
	};
}