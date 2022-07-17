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

void BaseApp::readUsersFromFile()
{
	std::ifstream myfile("/home/neronsuper/Documents/vsc projects/Messanger/Database/users.txt");
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
	}
	myfile.close();
}

std::string BaseApp::lastLine(std::string path)
{
	std::string lastline = " ";
	
	const std::string filename = path;
	std::ifstream fs;
	fs.open(filename.c_str(), std::fstream::in);
	if(fs.is_open())
	{
		//Got to the last character before EOF
		fs.seekg(-1, std::ios_base::end);
		if(fs.peek() == '\n')
		{
			//Start searching for \n occurrences
			fs.seekg(-1, std::ios_base::cur);
			int i = fs.tellg();
			for(i; i > 0; --i)
			{
				if(fs.peek() == '\n')
				{
					//Found
					fs.get();
					break;
				}
				//Move one character back
				fs.seekg(i, std::ios_base::beg);
			}
		}
		
		getline(fs, lastline);

	}
	else
	{
		std::cout << "Could not open file\n";
	}
	
	return lastline;
}

// void BaseApp::readFirstMesFromChats(UserData* userData)
// {
//     std::string path = "/home/neronsuper/Documents/vsc projects/Messanger/Database/users/";
//     path.append(userData->getLogin()).append("/chats/");
 
	
// 	for (auto & p : fs::directory_iterator(path))
// 	{
// 		std::string currentUser = p.path().filename().generic_string();
// 		std::string currentUserPath = p.path().generic_string();
		
// 		if (userData->getMessages().count(currentUser)) // if element exists
// 			userData->getMessages()[currentUser].get()->setMessage(lastLine(currentUserPath));
// 		else
// 			userData->getMessages()[currentUser] = std::make_unique<Message>(currentUser, lastLine(currentUserPath));
// 	}

// }

bool BaseApp::isUserExist(std::string& username)
{
	for (int i = 0; i < _usersData.size(); ++i)
	{
		if (_usersData[i]->getLogin() == username)
			return true;
	}

	return false;
}

bool BaseApp::isLoginAndPasswordCorrect(std::string& login, std::string& password)
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
	
	std::fstream myfile("/home/neronsuper/Documents/vsc projects/Messanger/Database/users.txt", std::ios::app);
	if (myfile.is_open())
	{
		myfile << userData->getLogin() << " " << userData->getPassword() << "\n";
	}
	myfile.close();
	

	createDirectory("/home/neronsuper/Documents/vsc projects/Messanger/Database/users/", userData->getLogin()); //creating main directory
	
	std::string mainDirectory("/home/neronsuper/Documents/vsc projects/Messanger/Database/users/");
	mainDirectory.append(userData->getLogin()).append("/");

	createDirectory(mainDirectory, "chats"); //creating chats

	_usersData.push_back(std::move(userData));
}

void BaseApp::createDirectory(std::string string_path, std::string directory_name)
{
	string_path.append(directory_name);
	int status = mkdir(string_path.c_str(),0777);
}

void BaseApp::sendMessage(const std::string& sender, const std::string& receiver, const std::string& message)
{
	std::string currentUser = "/home/neronsuper/Documents/vsc projects/Messanger/Database/users/"; // opening file current user 
    currentUser.append(sender).append("/chats/").append(receiver);

    std::string recipientUser = "/home/neronsuper/Documents/vsc projects/Messanger/Database/users/"; // opening recipient file user
    recipientUser.append(receiver).append("/chats/").append(sender);

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

void BaseApp::readFullChat(std::string chat)
{
	std::string currentUser = "/home/neronsuper/Documents/vsc projects/Messanger/Database/users/"; // opening file current user 
    currentUser.append(_userData->getLogin()).append("/chats/").append(chat);

    std::string tmp;
    std::ifstream in(currentUser); 

	_userData->clearChat(chat);

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