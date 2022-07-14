#pragma once
#include <string>
#include <iostream>


class PrivateUserData
{
public:
	PrivateUserData();
	PrivateUserData(const std::string &login, const std::string &password);
	PrivateUserData(const std::string& name, const std::string& login, const std::string& password);

	const std::pair<std::string, std::string>* getPData() const;
	const std::string& getName() const;

private:
	std::pair<std::string, std::string> _pData; 
	std::string _name;
	
	

};

