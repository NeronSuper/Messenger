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
	

private:

	PrivateUserData _privateUserData;

	std::map<std::string, std::vector<Message>> _messages;
	
};