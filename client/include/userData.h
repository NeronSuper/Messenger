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
	UserData(const std::string& login, const std::string& password);
	UserData& operator=(const UserData&);
	
	const std::string& getLogin() const;
	const std::string& getPassword() const;
	const std::vector<Message>& getMessages(std::string login);

	void setLogin(const std::string& login);
	void setPassword(const std::string& password);



	void addMessage(const std::string& receiver, const Message& mes);

private:

	PrivateUserData _privateUserData;

	std::map<std::string, std::vector<Message>> _messages;
	
};