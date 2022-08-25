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

UserData& UserData::operator=(const UserData& user)
{
	_privateUserData.setLogin(user.getLogin());
	_privateUserData.setPassword(user.getPassword());

	return *this;
}


const std::string& UserData::getLogin() const 
{
	return _privateUserData.getLogin();
}

const std::string& UserData::getPassword() const
{
	return _privateUserData.getPassword();
}

void UserData::setLogin(const std::string& login)
{

}

void UserData::setPassword(const std::string& password)
{
	
}

void UserData::addMessage(const Message& mes)
{
	_messages[mes.getOwner()].push_back(mes);
}