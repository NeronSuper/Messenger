#include "../include/baseApp.h"


namespace Messanger
{
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

	BaseApp::BaseApp() {}


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

			if (!isPassword(login, password))
				continue;


			break;
		}
		while(true);

		inAccount(findUser(login));
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

			if (isUser(login)) // if user exists
				continue;


			break;
		}
		while(true);
		
		addUser(UserData(login, password));
	}

	void BaseApp::inAccount(UserData* user)
	{
		_current = user;

		while(true)
		{
			std::system("cls");
			std::cout << "Account name: " << _current->getLogin() << '\n';
			std::cout << "1. Send a message\n";
			std::cout << "2. Look at a chat\n";
			std::cout << "3. Return\n";
			std::cout << "4. Exit\n";

			
			char response;
			std::cin >> response;

			switch(response)
			{
				case '1':
					sendMessage();
					break;
				case '2':
					lookAtChat();
					break;
				case '3':
					return;
				case '4':
					// need throw
				default:
					break;
			}
		}
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
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::getline(std::cin, message);

			if (!isUser(receiver))
				continue;

			
			break;
		}
		while(true);


		Message tmpMessage(_current->getLogin(), message);

		findUser(_current->getLogin())->addMessage(receiver, tmpMessage);
		findUser(receiver)->addMessage(_current->getLogin(), tmpMessage);
	}

	void BaseApp::lookAtChat()
	{
		std::string chat;
		do
		{
			std::system("cls");
			std::cout << "Chat: ";
			std::cin >> chat;

			if (!isUser(chat))
				continue;

			break;
		}
		while(true);

		printMessages(chat);
	}

	void BaseApp::printMessages(const std::string& chat)
	{
		auto messages = _current->getMessages(chat);

		std::system("cls");
		std::cout << "Your chat with " << chat << '\n';
		for(int i = 0; i < messages.size(); ++i)
		{
			std::cout << messages[i].getOwner() << ": " << messages[i].getMess() << '\n';
		}

		std::string tmp;
		std::cin >> tmp; // just for wait
	}

	bool BaseApp::isUser(const std::string& login)
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login)
				return true;
		}

		return false;
	}

	bool BaseApp::isPassword(const std::string& login, const std::string& password)
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login && _Users[i]->getPassword() == password)
				return true;
		}

		return false;
	}

	UserData* BaseApp::findUser(const std::string& login)
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login)
				return _Users[i].get();
		}

		return nullptr;
	}
}