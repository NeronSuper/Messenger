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
			std::cout << "1. Send a message\n";
			std::cout << "2. Look at a chat\n";
			std::cout << "3. Return\n";
			std::cout << "4. Exit\n";


			// std::cout << "1. List of your chats\n";
			// std::cout << "2. Start a new chat\n";
			// std::cout << "3. Log out of your account\n";
			// std::cout << "4. Exit\n";
			
			char response;
			std::cin >> response;

			switch(response)
			{
				case '1':
					send(_baseApp->ServerSocket(), "1", BUFFER_SIZE, 0);
					sendMessage();
					break;
				case '2':
					send(_baseApp->ServerSocket(), "2", BUFFER_SIZE, 0);
					lookAtChat();
					break;
				case '3':
					send(_baseApp->ServerSocket(), "3", BUFFER_SIZE, 0);
					return;
				case '4':
					// need throw
				default:
					break;
			}
		}

		_baseApp->SetCurrentUser(nullptr);
	}



	void CLIBaseApp::sendMessage()
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

			send(_baseApp->ServerSocket(), receiver.c_str(), BUFFER_SIZE, 0);

			if (!_baseApp->isUser(receiver, _baseApp->ServerSocket()))
				continue;

			
			break;
		}
		while(true);

		send(_baseApp->ServerSocket(), message.c_str(), BUFFER_SIZE, 0);
	}

	void CLIBaseApp::lookAtChat()
	{
		std::string chat;
		do
		{
			std::system("cls");
			std::cout << "Chat: ";
			std::cin >> chat;

			send(_baseApp->ServerSocket(), chat.c_str(), BUFFER_SIZE, 0);

			if (!_baseApp->isUser(chat, _baseApp->ServerSocket()))
				continue;

			break;
		}
		while(true);

		_baseApp->updateUserData();
		printMessages(chat);
	}

	void CLIBaseApp::printMessages(const std::string& chat)
	{
		UserData* _currentUser = _baseApp->GetCurrentUser();

		for (const auto& tmp : _currentUser->getMessages()[chat])
		{
			std::cout << tmp.getOwner() << ": " << tmp.getMess() << std::endl;
		}

		std::string tmp;
		std::cin >> tmp; // just for wait
	}
}