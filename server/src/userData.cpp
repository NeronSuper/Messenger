#include "../include/userData.h"

namespace Messanger
{
	UserData::UserData()
	{
		_messages = {};
	}

	UserData::UserData(const std::string& login, const std::string& password)
		: PrivateUserData(login, password)
	{
	}


	std::map<std::string, std::vector<Message>>& UserData::getMessages() 
	{
		return _messages;
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
}