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

std::pair<std::string, std::string>* PrivateUserData::getPData()
{
	return &_pData;
}
std::string* PrivateUserData::getName()
{
	return &_name;
}