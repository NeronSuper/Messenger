#pragma once
#include <string>
#include <iostream>


class PrivateUserData
{
public:
	PrivateUserData();
	PrivateUserData(const std::string& login, const std::string& password);

private:
	std::pair<std::string, std::string> _pData; 

	
};

