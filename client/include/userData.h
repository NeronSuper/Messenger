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
	
	const std::string& getLogin() const;
	const std::string& getPassword() const;

private:

	PrivateUserData _privateUserData;

	std::map<std::string, std::vector<Message>> _messages;
	
};