#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../src/message.cpp"
#include "../src/privateUserData.cpp"

class UserData
{
public:
	UserData();
	UserData(UserData&& copy);
	UserData(PrivateUserData const &privateUserData);

	void setLogin(const std::string& login);
	void setPassword(const std::string& password);
	void setName(const std::string& name);
	const Message* setMessage();
	void setMessageData(Message&& messageData);

	PrivateUserData* getPrivateUserData();
	std::map <std::string, std::unique_ptr<Message>>& getMessages();

private:
	std::unique_ptr<PrivateUserData> _privateUserData;
	std::map <std::string, std::unique_ptr<Message>> _messages = {};
	
};

