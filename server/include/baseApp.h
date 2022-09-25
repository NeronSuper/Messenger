#pragma once


#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT "666"
#define BUFFER_SIZE 512

#pragma comment(lib, "ws2_32.lib")


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <memory>
#include <conio.h>
#include <Windows.h>
#include <sstream>
#include <thread>

#include "../src/userData.cpp"


namespace Messanger
{
	class BaseApp
	{
	public:
		static BaseApp* instance();
	private:
		static BaseApp* _instance;

		BaseApp();
		~BaseApp() = delete;
		BaseApp(const BaseApp&);
		BaseApp& operator=(const BaseApp&);
		
	public:

		void addSocket(const SOCKET& ClientSocket);
		void addUser(const UserData& user);
		UserData* findUser(const std::string& login);
		void sendMessage(const Message& mes, UserData* sender, UserData* receiver);

		
	public:

		bool isUser(const std::string& login, const SOCKET& ClientSocket);
		bool isPassword(const std::string& login, const std::string& password, const SOCKET& ClientSocket);
		


		void updateUserData(UserData* _currentUser, const SOCKET& ClientSocket);

	private:
		std::vector<std::unique_ptr<UserData>> _Users;
		std::vector<SOCKET> _ClientsSockets;
	};
}