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
		: _Users(), _ClientsSockets()
	{
	}

	void BaseApp::addSocket(const SOCKET& ClientSocket)
	{
		_ClientsSockets.push_back(ClientSocket);
	}

	void BaseApp::addUser(const UserData& user)
	{
		std::cout << "Added user: " << user.getLogin() << " " << user.getPassword() << "\n";
		_Users.push_back(std::make_unique<UserData>(user));
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

	void BaseApp::sendMessage(const Message& mes, UserData* sender, UserData* receiver)
	{
		findUser(sender->getLogin())->addMessage(receiver->getLogin(), mes);
		findUser(receiver->getLogin())->addMessage(sender->getLogin(), mes);
	}

	bool BaseApp::isUser(const std::string& login, const SOCKET& ClientSocket)
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login)
			{
				send(ClientSocket, "1", 1, 0);
				return true;
			}
		}

		send(ClientSocket, "0", 1, 0);
		return false;
	}

	bool BaseApp::isPassword(const std::string& login, const std::string& password, const SOCKET& ClientSocket)
	{
		for (int i = 0; i < _Users.size(); ++i)
		{
			if (_Users[i]->getLogin() == login && _Users[i]->getPassword() == password)
			{
				send(ClientSocket, "1", 1, 0);
				return true;
			}
		}

		send(ClientSocket, "0", 1, 0);
		return false;
	}

	void BaseApp::updateUserData(UserData* _currentUser, const SOCKET& ClientSocket)
	{
		char buffer[BUFFER_SIZE];

		//send all messages which has user
		std::stringstream ss;


		int size_chats = static_cast<int>(_currentUser->getMessages().size());
		ss << size_chats;
		ss >> buffer;
		send(ClientSocket, buffer, BUFFER_SIZE, 0);


		for (auto map_iter = _currentUser->getMessages().begin(); map_iter != _currentUser->getMessages().end(); ++map_iter)
		{
			std::string tmp_userName = map_iter->first;
			std::vector<Message> tmp_messages = map_iter->second;

			

			send(ClientSocket, tmp_userName.c_str(), BUFFER_SIZE, 0);
			
			ss.clear();
			int size_messages = static_cast<int>(tmp_messages.size());
			ss << size_messages;
			ss >> buffer;
			send(ClientSocket, buffer, BUFFER_SIZE, 0);

			for (auto tmp_messages_iter = tmp_messages.begin(); tmp_messages_iter != tmp_messages.end(); ++tmp_messages_iter)
			{
				send(ClientSocket, tmp_messages_iter->getOwner().c_str(), BUFFER_SIZE, 0);
				send(ClientSocket, tmp_messages_iter->getMess().c_str(), BUFFER_SIZE, 0);
			}

		}
	}
}