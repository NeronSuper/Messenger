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

	BaseApp::BaseApp()
		: _current(nullptr), _ServerSocket(INVALID_SOCKET)
	{
		initSocket();
	}

	void BaseApp::initSocket()
	{
		WSADATA wsaData;
		ADDRINFO hints;
		ADDRINFO* addrResult = NULL;

		int iResult;

		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) 
		{
			std::cout << "WSAStartup failed, result = " << iResult << std::endl;
		}
		
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		iResult = getaddrinfo("localhost", PORT, &hints, &addrResult);
		if (iResult != 0) 
		{
			std::cout << "getaddrinfo failed, result = " << iResult << std::endl;
			WSACleanup();
		}

		_ServerSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
		if (_ServerSocket == INVALID_SOCKET) 
		{
			std::cout << "Socket creation failed" << std::endl;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		iResult = connect(_ServerSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			std::cout << "Unable connect to server" << std::endl;
			closesocket(_ServerSocket);
			_ServerSocket = INVALID_SOCKET;
			freeaddrinfo(addrResult);
			WSACleanup();
		}
	}


	void BaseApp::start()
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

			send(_ServerSocket, login.c_str(), BUFFER_SIZE, 0);
			send(_ServerSocket, password.c_str(), BUFFER_SIZE, 0);
			
			if (!isPassword(login, password))
				continue;


			break;
		}
		while(true);

		inAccount(new UserData(login, password));
	}

	void BaseApp::signUp()
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

			if (isUser(login)) // if user exists
				continue;


			break;
		}
		while(true);
		
		send(_ServerSocket, password.c_str(), BUFFER_SIZE, 0);
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

		delete _current;
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

			send(_ServerSocket, receiver.c_str(), BUFFER_SIZE, 0);

			if (!isUser(receiver))
				continue;

			
			break;
		}
		while(true);

		send(_ServerSocket, message.c_str(), BUFFER_SIZE, 0);
	}

	void BaseApp::lookAtChat()
	{
		std::string chat;
		do
		{
			std::system("cls");
			std::cout << "Chat: ";
			std::cin >> chat;

			send(_ServerSocket, chat.c_str(), BUFFER_SIZE, 0);

			if (!isUser(chat))
				continue;

			break;
		}
		while(true);

		printMessages(chat);
	}

	void BaseApp::printMessages(const std::string& chat)
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

	bool BaseApp::isUser(const std::string& login)
	{
		char buffer[BUFFER_SIZE];
		recv(_ServerSocket, buffer, BUFFER_SIZE, 0);

		return static_cast<int>(buffer[0]) - 48;
	}

	bool BaseApp::isPassword(const std::string& login, const std::string& password)
	{
		char buffer[BUFFER_SIZE];
		recv(_ServerSocket, buffer, BUFFER_SIZE, 0);

		return static_cast<int>(buffer[0]) - 48;
	}

	
}