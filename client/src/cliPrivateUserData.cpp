#include "../include/cliPrivateUserData.h"

CLIprivataUserData::CLIprivataUserData()
{
}
const std::string CLIprivataUserData::writeTempName()
{

	return "";
}

const std::string CLIprivataUserData::writeTempLogin()
{

	return "";
}

const std::string CLIprivataUserData::writeTempPassword()
{
	
	return "";
}

void CLIprivataUserData::help()
{
	std::cout << "1-> Receive messages" << std::endl;
	std::cout << "2-> Send a message to the user" << std::endl;
	std::cout << "3-> Send to all users" << std::endl;
	std::cout << "4-> Clear messages history" << std::endl;
	std::cout << "0-> Log out of account" << std::endl;

}
