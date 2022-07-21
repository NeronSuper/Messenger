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
	return _privateUserData->getLogin();
}

const std::string& UserData::getPassword() const
{
	return _privateUserData->getPassword();
}

const std::string& UserData::getName() const
{
	return _privateUserData->getName();
}

std::vector<Message>& UserData::getMessages(std::string& login)
{
	return _messages[login];
}

int UserData::getMessagesSize(std::string& login)
{
	return _messages[login].size();
}

void UserData::clearChat(std::string& chat)
{
	_messages[chat] = {};
}

void UserData::printMessages(const std::string& chat)
{
	auto messages = _messages[chat];
	for (auto i = messages.begin(); i != messages.end(); ++i)
	{
		std::cout << i->getMessage() << "\n";
	}
	
}

void UserData::pushMessBack(std::string& login, std::string& message)
{
	_messages[login].push_back(Message(login, message));
}

const Message* UserData::setMessage()
{
	Message* m = new Message(); 
	return m;
}



