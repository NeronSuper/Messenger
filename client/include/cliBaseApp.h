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

		void sendMessage();
		void lookAtChat();
		void printMessages(const std::string& chat);

        //void listOfChats();
        //void openChat();

    private:
        BaseApp* _baseApp;
        
        
        
    };
}