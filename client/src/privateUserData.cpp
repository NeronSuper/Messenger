#include "../include/privateUserData.h"

PrivateUserData::PrivateUserData()
{
	_name = {};
	_pData = {};
}

PrivateUserData::PrivateUserData(const std::string &login, const std::string& password)
	: PrivateUserData()
{
	_pData.first = login;
	_pData.second = password;
}

PrivateUserData::PrivateUserData(const std::string &name, const std::string &login, const std::string &password)
	: PrivateUserData(login, password)
{
	_name = name;
}

const std::pair<std::string, std::string>* PrivateUserData::getPData() const
{
	return &_pData;
}
const std::string& PrivateUserData::getName() const
{
	return _name;
}