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
	std::string login;
	std::string password;
	
	do
	{
		std::system("cls");
		std::cout << "Login: ";
		std::cin >> login;

		std::cout << "Password: ";
		std::cin >> password;

		if (!isUser(login, password))
			continue;


		break;
	}
	while(true);

	inAccount(UserData(login, password));
}

void BaseApp::signUp()
{
	std::string login;
	std::string password;
	
	do
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
	while(true);
	
	addUser(UserData(login, password));
}

void BaseApp::inAccount(const UserData& user)
{
	void (*print_menu)() = []()
	{
		std::system("cls");
		std::cout << "1. Send a message\n";
		std::cout << "2. Look at a chat\n";
		std::cout << "3. Return\n";
		std::cout << "4. Exit\n";
	};

	_current = new UserData(user);

	while(true)
	{
		print_menu();
		
		int response;
		std::cin >> response;

		switch(response)
		{
			case 1:
				sendMessage();
				break;
			case 2:
				
				break;
			case 3:
				return;
			case 4:
				
			default:
				break;
		}
	}


	delete _current;
}


void BaseApp::addUser(const UserData& user)
{
	_Users.push_back(std::make_unique<UserData>(user));
}

void BaseApp::sendMessage()
{
	std::string receiver;
	std::string message;
	do
	{	
		std::system("cls");
		std::cout << "Receiver: ";
		std::cin >> receiver;

		std::cout << "Message: ";
		std::cin >> message;

		if (!isUser(receiver, ""))
			continue;

		
		break;
	}
	while(true);


	Message tmpMessage(_current->getLogin(), message);


	_current->addMessage(tmpMessage);

	for(int i = 0; i < _Users.size(); ++i)
	{
		if (_Users[i]->getLogin() == receiver)
		{
			_Users[i]->addMessage(tmpMessage);
			break;	
		}
	}
}

void BaseApp::lookAtChat()
{
	
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