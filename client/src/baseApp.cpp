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
	{
	}

	

	bool BaseApp::isUser(const std::string& login, const SOCKET& ServerSocket)
	{
		char buffer[BUFFER_SIZE];
		recv(ServerSocket, buffer, BUFFER_SIZE, 0);

		return static_cast<int>(buffer[0]) - 48;
	}

	bool BaseApp::isPassword(const std::string& login, const std::string& password, const SOCKET& ServerSocket)
	{
		char buffer[BUFFER_SIZE];
		recv(ServerSocket, buffer, BUFFER_SIZE, 0);

		return static_cast<int>(buffer[0]) - 48;
	}

	void BaseApp::updateUserData(UserData* user)
	{


		//receive all messages which has user
		char buffer[BUFFER_SIZE];

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

	SOCKET& BaseApp::ServerSocket()
	{
		return _ServerSocket;
	}

	void BaseApp::SetCurrentUser(UserData* ud)
	{
		if (ud == nullptr)
		{
			delete _currentUser;	
		}
		_currentUser = ud;
	}

	const UserData* BaseApp::GetCurrentUser() const
	{
		return _currentUser;
	}

}