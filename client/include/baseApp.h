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
	static BaseApp* _instance;

	BaseApp();
	~BaseApp() = delete;
	BaseApp(const BaseApp&);
	BaseApp& operator=(const BaseApp&);
	
public:

	void start();

private:
	std::vector <std::unique_ptr<UserData>> _Users;
	UserData* _current;
};