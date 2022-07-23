#include "../include/cliMessage.h"

CLImessage::CLImessage()
{
    _baseApp = BaseApp::instance();
}

void CLImessage::help()
{
}

void CLImessage::sendMessage(std::string& receiver)
{
    std::string tmpMessage = "";
    do
    {
        std::system("clear");
        std::cout << "Your message to " << receiver << ": ";
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::getline(std::cin, tmpMessage);

        break;
    }
    while(1);

    _baseApp->sendMessage(_baseApp->getLogin(), receiver, tmpMessage);
}

void CLImessage::startNewChat()
{
    std::string receiver = "";
    do
    {
        std::system("clear");
        std::cout << "Start new chat with: ";
        std::cin >> receiver;

        if (receiver == _baseApp->getLogin())
        {
            std::cout << "You can't send a message to yourself\n";

            if (_baseApp->isContinue())
                continue;
            
            return;
        }

        if (!(_baseApp->isLoginExist(receiver)))
        {
            std::cout << "This user doesn't exist\n";

            if (_baseApp->isContinue())
                continue;
            
            return;
        }

        sendMessage(receiver);
        
        break;
    }
    while(1);
}

void CLImessage::openChat(std::string& chat)
{
    do 
    {
        std::system("clear");
        std::cout << "Chat opened with " << chat << "\n\n";
        
        _baseApp->readFullChat(chat);
        _baseApp->printMessages(chat);


        int userResponse;
        std::cout << "\n1. Update" <<
                     "\n2. Send a message"
                     "\n0. Close the chat\n";
        
        std::cin >> userResponse;

        switch (userResponse)
        {
        case 1:
            break;
        case 2:
            sendMessage(chat);
            break;
        default:
            return;
        }
    }
    while(true);
}

void CLImessage::listOfChats()
{
    int tmp;
    std::vector<std::string> folderNames = {};
    do
    {
        std::system("clear");

        _baseApp->setFolderNames(folderNames);

        if (folderNames.size() == 0) // if no chats
        {
            std::cout << "there is no chats started\n";
        }
        else
        {
            for (int i = 0; i < folderNames.size(); ++i)
            {
                std::cout << i + 1 << ". " << folderNames[i] << "\n";
            }
        }

        
        std::cout << "\nSelect chat or type \"0\" to return: ";
        std::cin >> tmp;

        if (tmp == 0)
            return;

        if (!(tmp > 0 && tmp <= folderNames.size()))
        {
            std::cout << "Incorrect input\n";

            if (_baseApp->isContinue())
                continue;
            
            return;
        }

        openChat(folderNames[tmp - 1]);

        break;
    } 
    while (true);
    
}

