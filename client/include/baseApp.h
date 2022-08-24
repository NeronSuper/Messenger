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





class BaseApp
{
public:
	static BaseApp* instance();
	
	
private:
	BaseApp();
	~BaseApp() = delete;
	BaseApp(const BaseApp&);
	BaseApp& operator=(const BaseApp&);
	
	static BaseApp* _instance;

	//std::vector <std::unique_ptr<UserData>> _usersData = {};
	//UserData* _userData;
};