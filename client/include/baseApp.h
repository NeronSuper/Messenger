#pragma once


//#pragma warning(disable: 4996)


#include "../src/userData.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <memory>
#include <unistd.h>
#include <experimental/filesystem>



namespace fs = std::experimental::filesystem;



class BaseApp
{
public:
	static BaseApp* instance();
	

	void addUser(std::unique_ptr<UserData>& userData);

	void sendMessage(const std::string& sender, const std::string& receiver, const std::string& message);
	bool isLoginAuth();
	bool isLoginExist(std::string& username);
	bool isUserExist(std::string& login, std::string& password);

	void setUserData(UserData* userData);
	void setFolderNames(std::vector<std::string>& folderNames);

	const std::string& getLogin() const;
	const std::string& getPassword() const;
	const std::string& getName() const;
	std::string getMyChatPath();
	std::string getNessesaryPath(std::vector<std::string>&& ways);

	void printMessages(const std::string& chat);
	bool isContinue();

	void createDirectory(std::string&& straight_path, std::string directory_name);
	
	void readUsersFromFile();
	void readFullChat(std::string& chat);

	~BaseApp() = delete;
private:
	BaseApp();
	BaseApp(const BaseApp&);
	BaseApp& operator=(const BaseApp&);
	static BaseApp* _instance;
	std::vector <std::unique_ptr<UserData>> _usersData = {};
	UserData* _userData;
	
};