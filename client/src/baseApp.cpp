#include "../include/baseApp.h"



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

BaseApp& BaseApp::operator=(const BaseApp&)
{
	return *this;
}

void BaseApp::setUserData(UserData* userData)
{
	this->_userData = userData;
}

const std::string& BaseApp::getLogin() const
{
	return _userData->getLogin();
}

const std::string& BaseApp::getPassword() const
{
	return _userData->getPassword();
}

const std::string& BaseApp::getName() const
{
	return _userData->getName();
}

void BaseApp::printMessages(const std::string& chat)
{
	_userData->printMessages(chat);
}

std::string BaseApp::getNessesaryPath(std::vector<std::string>&& ways)
{
	std::string tmp;
	for (auto i = ways.begin(); i != ways.end(); ++i)
	{
		tmp.append(*i);
	}
	
	return tmp;
}

std::string BaseApp::getMyChatPath()
{
	return getNessesaryPath(std::vector<std::string>{"../../../Database/users/", _userData->getLogin(), "/chats/"});
}

bool BaseApp::isContinue()
{
	std::string response;

	std::cout << "\nDo you want to continue?(y/n): ";
	std::cin >> response;

	if ((response == "y" || response == "Y")) // if something except y, Y
		return true;
	return false;
}

void BaseApp::readUsersFromFile()
{
	std::ifstream myfile("../../../Database/users.txt");
	std::string first_output;
	std::string second_output;
	
	
	if (myfile.is_open())
	{
		while (true)
		{
			myfile >> first_output >> second_output;
			if (myfile.eof()) 
				break;

			_usersData.push_back(std::make_unique<UserData>(PrivateUserData(first_output, second_output)));
		}
		
	}
	else
	{
		std::cout << "File can't be openned\n";
		std::exit(1);
	}
	myfile.close();
}

bool BaseApp::isLoginExist(std::string& username)
{
	for (int i = 0; i < _usersData.size(); ++i)
	{
		if (_usersData[i]->getLogin() == username)
			return true;
	}

	return false;
}

bool BaseApp::isUserExist(std::string& login, std::string& password)
{
	for (int i = 0; i < _usersData.size(); ++i)
	{
		if (_usersData[i]->getLogin() == login &&
			_usersData[i]->getPassword() == password)
			return true;
	}

	return false;
}

void BaseApp::addUser(std::unique_ptr<UserData>& userData)
{
	
	std::fstream myfile("../../../Database/users.txt", std::ios::app);
	if (myfile.is_open())
	{
		myfile << userData->getLogin() << " " << userData->getPassword() << "\n";
	}
	myfile.close();
	

	createDirectory("../../../Database/users/", userData->getLogin()); //creating user's directory
	createDirectory(getNessesaryPath(std::vector<std::string>{"../../../Database/users/", userData->getLogin(), "/"}), "chats"); //creating chats

	_usersData.push_back(std::move(userData));
}

void BaseApp::createDirectory(std::string&& straight_path, std::string directory_name)
{
	straight_path.append(directory_name);
	int status = mkdir(straight_path.c_str(),0777);
}

void BaseApp::setFolderNames(std::vector<std::string>& folderNames)
{
	std::string path = getMyChatPath();
	folderNames = {};
	for (auto & p : fs::directory_iterator(path))
	{
		folderNames.push_back(p.path().filename().generic_string());
	}
}

void BaseApp::sendMessage(const std::string& sender, const std::string& receiver, const std::string& message)
{
	std::string currentUser = getNessesaryPath(std::vector<std::string>{ "../../../Database/users/", sender, "/chats/", receiver}); // opening file current user 
    std::string recipientUser = getNessesaryPath(std::vector<std::string>{ "../../../Database/users/", receiver, "/chats/", sender}); // opening recipient file user

    std::fstream currentUserFile(currentUser, std::ios::app);
    std::fstream recipientUserFile(recipientUser, std::ios::app);
	if (currentUserFile.is_open() && recipientUserFile.is_open())
	{
		currentUserFile << sender << ": " << message << "\n";
        recipientUserFile << sender << ": " << message << "\n";
	}
	currentUserFile.close();
    recipientUserFile.close();
}

void BaseApp::readFullChat(std::string& chat)
{
	_userData->clearChat(chat);


	std::ifstream in(getNessesaryPath(std::vector<std::string>{"../../../Database/users/", _userData->getLogin(), "/chats/", chat})); 

    std::string tmp;
    if (in.is_open())
    {
        std::system("clear");
        while (getline(in, tmp))
        {
            _userData->pushMessBack(chat, tmp);
        }
    }
    in.close(); 
}