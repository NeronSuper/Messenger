#include "../include/cliBaseApp.h"


namespace Messanger
{
    CLIBaseApp::CLIBaseApp(SOCKET ClientSocket)
        : _baseApp(BaseApp::instance()), _currentUser(), _currentSocket(ClientSocket)
    {

    }

    void CLIBaseApp::start()
	{

		while(true)
		{
			int response;
			
			char buffer[BUFFER_SIZE];
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);

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

	void CLIBaseApp::signIn()
	{
		std::string login;
		std::string password;
		
		char buffer[512];

		do
		{
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			login = buffer;

			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			password = buffer;

			if (!_baseApp->isPassword(login, password, _currentSocket))
				continue;


			break;
		}
		while(true);

		inAccount(_baseApp->findUser(login));
	}

	void CLIBaseApp::signUp()
	{
		std::string login;
		std::string password;

		
		char buffer[BUFFER_SIZE];
		do
		{
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			login = buffer;

			if (_baseApp->isUser(login, _currentSocket)) // if user exists
				continue;


			break;
		}
		while(true);

		recv(_currentSocket, buffer, BUFFER_SIZE, 0);
		password = buffer;
		
		_baseApp->addUser({login, password});
	}

	void CLIBaseApp::inAccount(UserData* user)
	{
		_currentUser = user;

		while(true)
		{
			char buffer[BUFFER_SIZE];
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);

			char response = buffer[0];

			switch(response)
			{
				case '1':
					startNewChat();
					break;
				case '2':
					listOfChats();
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

    void CLIBaseApp::startNewChat()
	{
		do
		{
			char buffer[BUFFER_SIZE];
			std::string receiver;

			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			receiver = buffer;

			if (!_baseApp->isUser(receiver, _currentSocket))
				continue;


			sendMessage();

			break;
		}
		while(true);
	}

	void CLIBaseApp::listOfChats()
	{

		do
		{
			_baseApp->updateUserData(_currentUser, _currentSocket);

			char buffer[BUFFER_SIZE];
			std::string tmp;
			std::stringstream ss;
			int input_from_user;

			
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			tmp = buffer;

			ss << tmp;
			ss >> input_from_user;
			
			if (input_from_user == 0)
			{
				return;
			}

			openChat();

			break;
		}
		while(true);
	}

	void CLIBaseApp::openChat()
	{
		char buffer[BUFFER_SIZE];

		std::string chat;
		recv(_currentSocket, buffer, BUFFER_SIZE, 0);
		chat = buffer;


		char isKbhit;
		do
		{
			printChat();

			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			isKbhit = buffer[0];
			if (isKbhit == '1')
			{
				recv(_currentSocket, buffer, BUFFER_SIZE, 0);
				char input_from_user = buffer[0];
				
				switch (input_from_user)
				{
				case '1':
					sendMessage();

					break;
				case '0':
					return;
				default:
					break;
				}
			}
		}
		while(true);
	}

	void CLIBaseApp::printChat()
	{
		_baseApp->updateUserData(_currentUser, _currentSocket);
	}

	void CLIBaseApp::sendMessage()
	{
		char buffer[BUFFER_SIZE];

		std::string message;
		std::string receiver;
		
		recv(_currentSocket, buffer, BUFFER_SIZE, 0);
		message = buffer;

		recv(_currentSocket, buffer, BUFFER_SIZE, 0);
		receiver = buffer;

		Message mes(_currentUser->getLogin(), message);
        UserData* user_receiver = _baseApp->findUser(receiver);

		_baseApp->sendMessage(mes, _currentUser, user_receiver);
	}
}