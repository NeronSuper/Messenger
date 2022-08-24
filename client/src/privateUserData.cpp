#include "../include/privateUserData.h"

PrivateUserData::PrivateUserData()
{
	_pData = {};
}

PrivateUserData::PrivateUserData(const std::string& login, const std::string& password)
	: _pData(login, password)
{
}