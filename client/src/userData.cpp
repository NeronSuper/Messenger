#include "../include/userData.h"

UserData::UserData()
{
	_messages = {};
	_privateUserData = {};
}

UserData::UserData(const std::string& login, const std::string& password)
	: _privateUserData(login, password)
{
}


const std::string& UserData::getLogin() const 
{
	return _privateUserData.getLogin();
}

const std::string& UserData::getPassword() const
{
	return _privateUserData.getPassword();
}