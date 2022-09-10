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

		void initSocket();

		void start();
		void signIn();
		void signUp();
		void inAccount(UserData* user);

		void sendMessage();
		void lookAtChat();
		void printMessages(const std::string& chat);
	public:

		void addUser(const UserData& user);
		bool isUser(const std::string& login);
		bool isPassword(const std::string& login, const std::string& password);
		UserData* findUser(const std::string& login);
		

	private:
		std::vector <std::unique_ptr<UserData>> _Users;
		UserData* _current;
		SOCKET _ClientsSockets;
	};
}