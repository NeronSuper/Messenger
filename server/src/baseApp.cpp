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
		: _Users(), _current(nullptr), _ClientsSockets(INVALID_SOCKET)
	{
		initSocket();
	}

	void BaseApp::initSocket()
	{
		WSADATA wsaData;
		ADDRINFO hints;
		ADDRINFO* addrResult = NULL;

		SOCKET ListenSocket;

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

		ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) 
		{
			std::cout << "Socket creation failed" << std::endl;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		iResult = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			std::cout << "Binding socket failed" << std::endl;
			closesocket(ListenSocket);
			ListenSocket = INVALID_SOCKET;
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR)
		{
			std::cout << "Listening socket failed" << std::endl;
			closesocket(ListenSocket);
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		_ClientsSockets = accept(ListenSocket, NULL, NULL);
		if (_ClientsSockets == INVALID_SOCKET)
		{
			std::cout << "Accepting socket failed" << std::endl;
			closesocket(ListenSocket);
			freeaddrinfo(addrResult);
			WSACleanup();
		}

		std::cout << "Client is connected\n";
	}


	void BaseApp::start()
	{

		while(true)
		{
			int response;
			
			char buffer[BUFFER_SIZE];
			recv(_ClientsSockets, buffer, BUFFER_SIZE, 0);

			response = static_cast<int>(buffer[0]) - 48;


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
			//std::system("cls");
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

		
		char buffer[BUFFER_SIZE];
		do
		{
			recv(_ClientsSockets, buffer, BUFFER_SIZE, 0);
			login = buffer;

			if (isUser(login)) // if user exists
				continue;


			break;
		}
		while(true);

		recv(_ClientsSockets, buffer, BUFFER_SIZE, 0);
		password = buffer;
		
		addUser({login, password});
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
			{
				send(_ClientsSockets, "1", 1, 0);
				return true;
			}
		}

		send(_ClientsSockets, "0", 1, 0);
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