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
        void startNewChat();
        void listOfChats();
        void openChat(const std::string& chat);

		void printChat(const std::string& chat);
		void sendMessage(const std::string& receiver);


    private:
        BaseApp* _baseApp;
    };
}