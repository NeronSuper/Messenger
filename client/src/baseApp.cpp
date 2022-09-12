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

	
}