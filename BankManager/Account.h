#pragma once

//#ifdef ACCOUNT_EXPORTS
#define ACCOUNT_API _declspec(dllexport)
//#else
//#define ACCOUNT_API _declspec(dllimport)
//#endif // ACCOUNT_EXPORTS

class ACCOUNT_API Account
{
public:
	int Add(int a, int b);
};

