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