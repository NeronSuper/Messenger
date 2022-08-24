#include "../include/baseApp.h"



BaseApp* BaseApp::_instance = 0;
BaseApp* BaseApp::instance()
{
	if (_instance == 0)
	{
		// use unique_ptr insted new
		_instance = new BaseApp;
	}
	return _instance;
}

BaseApp::BaseApp() 
{
	_current = new UserData;
}

void BaseApp::start()
{
	void (*print_menu)() = []()
	{
		std::system("cls");
		std::cout << "1. Sign in\n";
		std::cout << "2. Sign up\n";
		std::cout << "3. Exit\n";
	};

	while(true)
	{
		print_menu();
		
		int response;
		std::cin >> response;

		switch(response)
		{
			case 1:
				signIn();
				break;
			case 2:
				signUp();
				break;
			case 3:
				return;
			default:
				break;
		}
	}
}

void BaseApp::signIn()
{

}

void BaseApp::signUp()
{
	std::string login;
	std::string password;
	
	while(true)
	{
		std::system("cls");
		std::cout << "Login: ";
		std::cin >> login;

		std::cout << "Password: ";
		std::cin >> password;

		if (isUser(login, "")) // if user exists
			continue;


		break;
	}

	addUser(UserData(login, password));
}


void BaseApp::addUser(const UserData& user)
{
	_Users.push_back(std::make_unique<UserData>(user));
}


bool BaseApp::isUser(const std::string& login, const std::string& password)
{
	if (password == "")
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login)
				return true;
		}
		
	}
	else
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login && _Users[i]->getPassword() == password)
				return true;
		}
	}

	return false;
}