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
	void clearChat(std::string& chat);
	void pushMessBack(std::string& login, std::string& message);

	void printMessages(const std::string& chat);

	const std::string& getLogin() const;
	const std::string& getPassword() const;
	const std::string& getName() const;
	std::vector<Message>& getMessages(std::string& login);
	int getMessagesSize(std::string& login);

private:
	std::unique_ptr<PrivateUserData> _privateUserData;
	std::map <std::string, std::vector<Message>> _messages = {};
	
};

