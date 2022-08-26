#include "../include/userData.h"

UserData::UserData()
{
	_messages = {};
}

UserData::UserData(const std::string& login, const std::string& password)
	: PrivateUserData(login, password)
{
}


const std::vector<Message>& UserData::getMessages(std::string login) 
{
	return _messages[login];
}

void UserData::setLogin(const std::string& login)
{

}

void UserData::setPassword(const std::string& password)
{
	
}

void UserData::addMessage(const std::string& receiver, const Message& mes)
{
	_messages[receiver].push_back(mes);
}