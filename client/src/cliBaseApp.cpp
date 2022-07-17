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
    std::cout << "1. Send a massage\n";
    std::cout << "2. Look at a chat\n";
    std::cout << "0. Log out of your account\n";
}

void CLIBaseApp::signIn()
{
	do
	{
		std::string login;
		std::string password;

		std::system("clear");
		std::cout << "Your login: ";
		std::cin >> login;
		std::cout << "Your password: ";
		std::cin >> password;

		if (_baseApp->isLoginAndPasswordCorrect(login, password))
		{
			_userData = std::make_unique<UserData>(PrivateUserData(login, password));
			_baseApp->setUserData(_userData.get());

			break;
		}
	}
	while (true);
	
	CLImessage cliMessage;
	CLI* cli = &cliMessage;
	
	while(true)
	{
		menu_CBA();

		int requestToUser;
		std::cin >> requestToUser;

		switch (requestToUser)
		{
		case 1:
			cliMessage.sendMessage();
			break;
		case 2:
			cliMessage.showChat();
			break;
		case 0:
			_userData = {};
			return;
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

		
		if (_baseApp->isUserExist(login))
			continue;
		

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