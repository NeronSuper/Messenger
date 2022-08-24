#include "../include/privateUserData.h"

PrivateUserData::PrivateUserData()
{
	_pData = {};
}

PrivateUserData::PrivateUserData(const std::string& login, const std::string& password)
	: _pData(login, password)
{
}

const std::string& PrivateUserData::getLogin() const
{
	return _pData.first;
}

const std::string& PrivateUserData::getPassword() const
{
	return _pData.second;
}