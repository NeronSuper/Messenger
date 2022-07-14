#include "../include/userData.h"



UserData::UserData()
{
	_privateUserData = {};
}

UserData::UserData(UserData&& copy) 
	: _privateUserData(std::move(copy._privateUserData)), _messages(std::move(copy._messages))
{
	
}

UserData::UserData(PrivateUserData const &privateUserData)
	: _privateUserData(std::make_unique<PrivateUserData>(privateUserData))
{
	
}




void UserData::setLogin(const std::string& login)
{
	
}

void UserData::setPassword(const std::string& password)
{
	
}

void UserData::setName(const std::string& name)
{

}

const std::string& UserData::getLogin() const
{
	return _privateUserData.get()->getPData()->first;
}

const std::string& UserData::getPassword() const
{
	return _privateUserData.get()->getPData()->second;
}

const std::string& UserData::getName() const
{
	return _privateUserData.get()->getName();
}

const Message* UserData::setMessage()
{
	Message* m = new Message(); 
	return m;
}

void UserData::setMessageData(Message&& messageData)
{
	_messages[messageData.getLogin()] = std::make_unique<Message>(messageData);
}

PrivateUserData* UserData::getPrivateUserData()
{
	return _privateUserData.get();
}

std::map<std::string, std::unique_ptr<Message>>& UserData::getMessages()
{
	return _messages;
}



