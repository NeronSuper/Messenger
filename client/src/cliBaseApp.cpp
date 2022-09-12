#include "../include/cliBaseApp.h"


namespace Messanger
{
    CLIBaseApp::CLIBaseApp(SOCKET ServerSocket)
        : _baseApp(BaseApp::instance()), _currentUser(), _ServerSocket(ServerSocket)
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
					send(_ServerSocket, "1", BUFFER_SIZE, 0);
					signIn();

					break;
				case 2:
					send(_ServerSocket, "2", BUFFER_SIZE, 0);
					signUp();

					break;
				case 3:
					send(_ServerSocket, "3", BUFFER_SIZE, 0);
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

			send(_ServerSocket, login.c_str(), BUFFER_SIZE, 0);
			send(_ServerSocket, password.c_str(), BUFFER_SIZE, 0);
			
			if (!_baseApp->isPassword(login, password, _ServerSocket))
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
			std::cout << "I'Am here\n";
			std::cout << "Login: ";
			std::cin >> login;

			std::cout << "Password: ";
			std::cin >> password;

			send(_ServerSocket, login.c_str(), BUFFER_SIZE, 0);

			if (_baseApp->isUser(login, _ServerSocket)) // if user exists
				continue;


			break;
		}
		while(true);
		
		send(_ServerSocket, password.c_str(), BUFFER_SIZE, 0);
	}

	void CLIBaseApp::inAccount(UserData* user)
	{
		_currentUser = user;

		while(true)
		{
			std::system("cls");
			std::cout << "Account name: " << _currentUser->getLogin() << '\n';
			std::cout << "1. Send a message\n";
			std::cout << "2. Look at a chat\n";
			std::cout << "3. Return\n";
			std::cout << "4. Exit\n";

			
			char response;
			std::cin >> response;

			switch(response)
			{
				case '1':
					send(_ServerSocket, "1", BUFFER_SIZE, 0);
					sendMessage();
					break;
				case '2':
					send(_ServerSocket, "2", BUFFER_SIZE, 0);
					lookAtChat();
					break;
				case '3':
					send(_ServerSocket, "3", BUFFER_SIZE, 0);
					return;
				case '4':
					// need throw
				default:
					break;
			}
		}

		delete _currentUser;
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

			send(_ServerSocket, receiver.c_str(), BUFFER_SIZE, 0);

			if (!_baseApp->isUser(receiver, _ServerSocket))
				continue;

			
			break;
		}
		while(true);

		send(_ServerSocket, message.c_str(), BUFFER_SIZE, 0);
	}

	void CLIBaseApp::lookAtChat()
	{
		std::string chat;
		do
		{
			std::system("cls");
			std::cout << "Chat: ";
			std::cin >> chat;

			send(_ServerSocket, chat.c_str(), BUFFER_SIZE, 0);

			if (!_baseApp->isUser(chat, _ServerSocket))
				continue;

			break;
		}
		while(true);

		printMessages(chat);
	}

	void CLIBaseApp::printMessages(const std::string& chat)
	{
		char buffer[BUFFER_SIZE];


		std::system("cls");
		std::cout << "Your chat with " << chat << '\n';

		recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
		int size_messages;
		std::stringstream ss;
		ss << buffer;
		ss >> size_messages;

		for(int i = 0; i < size_messages; ++i)
		{
			std::string login;
			recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
			login = buffer;

			std::string message;
			recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
			message = buffer;

			std::cout << login << ": " << message << '\n';
		}

		std::string tmp;
		std::cin >> tmp; // just for wait
	}
}