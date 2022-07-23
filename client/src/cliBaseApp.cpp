#include "../include/cliBaseApp.h"
#include "cliPrivateUserData.cpp"
#include "cliMessage.cpp"


CLIBaseApp::CLIBaseApp()
{
	_baseApp = BaseApp::instance();
}

void CLIBaseApp::menu_CBA()
{
	std::system("clear");
	std::cout << "User name: " << _userData->getLogin() << "\n";
    std::cout << "1. List of Chats\n";
	std::cout << "2. Start a new chat\n";
    std::cout << "0. Log out of your account\n";
}

void CLIBaseApp::signIn()
{
	do
	{
		std::string login, password, response;

		std::system("clear");
		std::cout << "Your login: ";
		std::cin >> login;
		std::cout << "Your password: ";
		std::cin >> password;

		if (_baseApp->isUserExist(login, password))
		{
			_userData = std::make_unique<UserData>(PrivateUserData(login, password));
			_baseApp->setUserData(_userData.get());

			break;
		}

		std::cout << "Incorrect login or password\n";

		if (_baseApp->isContinue())
            continue;
            
        return;
	}
	while (true);
	
	CLImessage cliMessage;
	CLI* cli = &cliMessage;
	
	while(true)
	{
		menu_CBA();

		char requestToUser;
		std::cin >> requestToUser;

		switch (requestToUser)
		{
		case '1':
			cliMessage.listOfChats();
			break;
		case '2':
			cliMessage.startNewChat();
			break;
		case '0':
			_userData = {};
			return;
		default:
			break;
		}
	}	
}

void CLIBaseApp::signUp()
{

	std::string login;
	std::string password;
	do
	{
		std::system("clear");
		std::cout << "Username: ";
		std::cin >> login;

		
		if (_baseApp->isLoginExist(login))
		{
			std::cout << "This user already exists\n";
			
			if (_baseApp->isContinue())
                continue;
            
            return;
		}
		

		std::cout << "Password: ";
		std::cin >> password;

		break;
	}
	while (true);

	
	auto tmp = std::make_unique<UserData>(PrivateUserData(login, password));

	_baseApp->addUser(tmp);

	//this->signIn();

}

void CLIBaseApp::help()
{
	std::system("clear");
	std::cout << "0. To terminate the program" << std::endl;
	std::cout << "1. Sign in" << std::endl;
	std::cout << "2. Sign up" << std::endl;
	int requestToUser;
	std::cin >> requestToUser;
	switch (requestToUser)
	{
	case 0:
		exit(0);
		break;
	}
}