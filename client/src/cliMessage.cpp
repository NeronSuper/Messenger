#include "../include/cliMessage.h"

CLImessage::CLImessage(UserData* _userData)
    : _userData(_userData)
{
    _baseApp = nullptr;
}

void CLImessage::help()
{
}

void CLImessage::sendMessage()
{
    _baseApp = BaseApp::instance();

    std::system("clear");

    std::string receiver = "";
    std::string tmpMessage = "";
    do
    {
        std::cout << "Message to: ";
        std::cin >> receiver;
        if (!_baseApp->isUserExist(receiver))
        {
            continue;
        }
        std::cout << "Your message to " << receiver << ": ";
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::getline(std::cin, tmpMessage);

        break;
    }
    while(1);

    Message ms(_userData->getPrivateUserData()->getPData()->first, tmpMessage);
    _baseApp->sendMessage(ms, receiver);

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
    std::string tmpLastline = "";
    do
    {
        _baseApp->readFirstMesFromChats(_userData); // reading first messages from all chats
        
        if (tmpLastline != _userData->getMessages()[chat].get()->getMessage()) // if message is new, reread it
        {
            _baseApp->readFullChat(_userData, chat);
        }

        std::system("clear");
        for (int i = 0; i < _userData->getMessages()[chat].get()->getMessages().size(); i++) // print messages
        {
            std::cout << _userData->getMessages()[chat].get()->getMessages()[i] << "\n";
        }

        tmpLastline = _userData->getMessages()[chat].get()->getMessage(); // write oldest message
        

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