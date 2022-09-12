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

    void CLIBaseApp::sendMessage()
	{
		char buffer[BUFFER_SIZE];

		std::string receiver;
		do
		{	
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			receiver = buffer;

			if (!_baseApp->isUser(receiver, _currentSocket))
				continue;

			
			break;
		}
		while(true);

        std::string tmpMessage;
		recv(_currentSocket, buffer, BUFFER_SIZE, 0);
		tmpMessage = buffer;

		Message mes(_currentUser->getLogin(), tmpMessage);
        UserData* user_receiver = _baseApp->findUser(receiver);

		_baseApp->sendMessage(mes, _currentUser, user_receiver);
	}

	void CLIBaseApp::lookAtChat()
	{
		char buffer[BUFFER_SIZE];

		std::string chat;
		do
		{
			recv(_currentSocket, buffer, BUFFER_SIZE, 0);
			chat = buffer;

			if (!_baseApp->isUser(chat, _currentSocket))
				continue;

			break;
		}
		while(true);

		printMessages(chat);
	}

	void CLIBaseApp::printMessages(const std::string& chat)
	{
		char buffer[BUFFER_SIZE];

		auto messages = _currentUser->getMessages(chat);

		std::stringstream ss;
		ss << messages.size();
		ss >> buffer;
		send(_currentSocket, buffer, BUFFER_SIZE, 0);
		for(int i = 0; i < messages.size(); ++i)
		{
			send(_currentSocket, messages[i].getOwner().c_str(), BUFFER_SIZE, 0);
			send(_currentSocket, messages[i].getMess().c_str(), BUFFER_SIZE, 0);
		}
	}
}