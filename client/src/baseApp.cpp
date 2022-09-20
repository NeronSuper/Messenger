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

	void BaseApp::updateUserData()
	{
		char buffer[BUFFER_SIZE];

		//receive all messages which has user
		std::stringstream ss;


		int size_chats = 0;
		recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
		ss << buffer;
		ss >> size_chats;

		
		for (int i = 0; i < size_chats; ++i)
		{
			
			std::string tmp_userName;
			std::vector<Message> tmp_messages;

			recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
			tmp_userName = buffer;

			int size_messages = 0;
			recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
			ss.clear();
			ss << buffer;
			ss >> size_messages;


			for (int i = 0; i < size_messages; ++i)
			{
				std::string tmp_senderName;
				recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
				tmp_senderName = buffer;
				recv(_ServerSocket, buffer, BUFFER_SIZE, 0);
				tmp_messages.push_back(Message(tmp_senderName, buffer));
			}

			_currentUser->getMessages()[tmp_userName] = tmp_messages;


			
		}
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

	UserData* BaseApp::GetCurrentUser()
	{
		return _currentUser;
	}

}