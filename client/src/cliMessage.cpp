#include "../include/cliMessage.h"

CLImessage::CLImessage()
{
    _baseApp = BaseApp::instance();
}

void CLImessage::help()
{
}

void CLImessage::sendMessage()
{
    std::system("clear");

    std::string receiver = "";
    std::string tmpMessage = "";
    do
    {
        std::cout << "Message to: ";
        std::cin >> receiver;

        if (!_baseApp->isUserExist(receiver))
        {
            std::cout << "This user doesn't exist\n";
            continue;
        }

        std::cout << "Your message to " << receiver << ": ";
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::getline(std::cin, tmpMessage);

        break;
    }
    while(1);

    _baseApp->sendMessage(_baseApp->getLogin(), receiver, tmpMessage);
}

void CLImessage::showChat()
{
    
    std::string chat;
    do
    {
        std::system("clear");

        std::cout << "Enter currect chat which you wanna see: ";
        std::cin >> chat;

        // here have to be check if it exists

        break;
    } 
    while (1);

    std::string tmp;
    int userResponse;
    do
    {
        
        _baseApp->readFullChat(chat);
        

        std::system("clear");
        _baseApp->printMessages(chat);
        

        std::cout << "\n1. Update\n" <<
                       "2. Close the chat\n";
        
        std::cin >> userResponse;

        switch (userResponse)
        {
        case 1:
            break;
        case 2:
            return;
        default:
            break;
        }
    }
    while (1);
}