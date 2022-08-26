#pragma once


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <memory>
#include <conio.h>
#include <Windows.h>

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
	};
}