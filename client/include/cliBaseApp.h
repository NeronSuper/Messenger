#pragma once
#include "baseApp.h"

namespace Messanger
{
    class CLIBaseApp
    {
    public:
        CLIBaseApp();

        void start();

    private:

		void signIn();
		void signUp();
		void inAccount(UserData* user);

		void sendMessage(const std::string& receiver);
		void printChat(const std::string& chat);

        void listOfChats();
        void openChat(const std::string& chat);
        void startNewChat();

    private:
        BaseApp* _baseApp;
        
        
        
    };
}