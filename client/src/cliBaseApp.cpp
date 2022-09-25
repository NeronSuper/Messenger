#include "../include/cliBaseApp.h"


namespace Messanger
{
    CLIBaseApp::CLIBaseApp()
        : _baseApp(BaseApp::instance())
    {

    }

    void CLIBaseApp::start()
	{

		while(true)
		{
			std::system("cls");
			std::cout << "1. Sign in\n";
			std::cout << "2. Sign up\n";
			std::cout << "3. Exit\n";
			
			int response;
			std::cin >> response;

			switch(response)
			{
				case 1:
					send(_baseApp->ServerSocket(), "1", BUFFER_SIZE, 0);
					signIn();

					break;
				case 2:
					send(_baseApp->ServerSocket(), "2", BUFFER_SIZE, 0);
					signUp();

					break;
				case 3:
					send(_baseApp->ServerSocket(), "3", BUFFER_SIZE, 0);
					return;
				default:
					break;
			}
		}
	}

	void CLIBaseApp::signIn()
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

			send(_baseApp->ServerSocket(), login.c_str(), BUFFER_SIZE, 0);
			send(_baseApp->ServerSocket(), password.c_str(), BUFFER_SIZE, 0);
			
			if (!_baseApp->isPassword(login, password, _baseApp->ServerSocket()))
				continue;


			break;
		}
		while(true);

		inAccount(new UserData(login, password));
	}

	void CLIBaseApp::signUp()
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

			send(_baseApp->ServerSocket(), login.c_str(), BUFFER_SIZE, 0);

			if (_baseApp->isUser(login, _baseApp->ServerSocket())) // if user exists
				continue;


			break;
		}
		while(true);
		
		send(_baseApp->ServerSocket(), password.c_str(), BUFFER_SIZE, 0);
	}

	void CLIBaseApp::inAccount(UserData* user)
	{
		_baseApp->SetCurrentUser(user);

		while(true)
		{
			std::system("cls");
			std::cout << "Account name: " << _baseApp->GetCurrentUser()->getLogin() << '\n';
			std::cout << "1. Start a new chat\n";
			std::cout << "2. List of your chats\n";
			std::cout << "3. Return\n";
			std::cout << "4. Exit\n";

			
			char response;
			std::cin >> response;

			switch(response)
			{
				case '1':
					send(_baseApp->ServerSocket(), "1", BUFFER_SIZE, 0);
					startNewChat();
					break;
				case '2':
					send(_baseApp->ServerSocket(), "2", BUFFER_SIZE, 0);
					listOfChats();
					break;
				case '3':
					send(_baseApp->ServerSocket(), "3", BUFFER_SIZE, 0);
					_baseApp->SetCurrentUser(nullptr);
					return;
				case '4':
					// need throw
				default:
					break;
			}
		}

	}



	void CLIBaseApp::sendMessage(const std::string& receiver)
	{
		std::string message;
		do
		{	
			std::cout << "Message: ";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::getline(std::cin, message);

			if (message[0] == '\n')
				continue;
			
			break;
		}
		while(true);

		send(_baseApp->ServerSocket(), message.c_str(), BUFFER_SIZE, 0);
	}

	void CLIBaseApp::printChat(const std::string& chat)
	{
		_baseApp->updateUserData();

		UserData* _currentUser = _baseApp->GetCurrentUser();

		for (const auto& tmp : _currentUser->getMessages()[chat])
		{
			std::cout << tmp.getOwner() << ": " << tmp.getMess() << std::endl;
		}

		std::string tmp;
		std::cin >> tmp; // just for wait
	}

	void CLIBaseApp::listOfChats()
	{
		auto& messages = _baseApp->GetCurrentUser()->getMessages();

		do
		{
			_baseApp->updateUserData();

			std::system("cls");

			int i = 1; // printing chats
			for	(auto iter = messages.begin(); iter != messages.end(); ++i, ++iter)
			{
				std::cout << i << ". " << iter->first << "\n";
			}
			std::cout << "0. Return\n";

			int input_from_user;
			std::cin >> input_from_user;

			if (input_from_user < 0 || input_from_user > i) // cheking if user wrote correct number
				continue;

			std::stringstream ss;
			std::string tmp;
			ss << input_from_user;
			ss >> tmp;
			send(_baseApp->ServerSocket(), tmp.c_str(), BUFFER_SIZE, 0);
			if (input_from_user == 0)
			{
				return;
			}

			auto iter = messages.begin(); // picking correct user
			for (i = 1; i != input_from_user; ++i)
			{
				++iter;
			}

			openChat(iter->first); // opening chat

			break;
		}
		while(true);
	}

	void CLIBaseApp::openChat(const std::string& chat)
	{
		do
		{
			printChat(chat);

			std::system("cls");
			std::cout << "1. Send a message\n";
			std::cout << "0. Close the chat\n";

			if (_kbhit())
			{
				char input_from_user = _getch();
				switch (input_from_user)
				{
				case '1':
					send(_baseApp->ServerSocket(), "1", BUFFER_SIZE, 0);
					sendMessage(chat);

					break;
				case '0':
					send(_baseApp->ServerSocket(), "0", BUFFER_SIZE, 0);

					return;
				default:
					break;
				}
			}
		}
		while(true);
	}

	void CLIBaseApp::startNewChat()
	{
		std::string receiver;
		do
		{
			std::system("cls");
			std::cout << "Enter user name: ";
			std::cin >> receiver;

			send(_baseApp->ServerSocket(), receiver.c_str(), BUFFER_SIZE, 0);

			if (!_baseApp->isUser(receiver, _baseApp->ServerSocket()))
				continue;


			sendMessage(receiver);

			break;
		}
		while(true);
	}
}