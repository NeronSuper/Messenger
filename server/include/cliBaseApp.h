#pragma once
#include "baseApp.h"

namespace Messanger
{
    class CLIBaseApp
    {
    public:
        CLIBaseApp(SOCKET ClientSocket);

        void start();

    private:

		void signIn();
		void signUp();

		void inAccount(UserData* user);
		void startNewChat();
        void listOfChats();
        void openChat();

		void printChat();
		void sendMessage();

    private:
        BaseApp* _baseApp;
        UserData* _currentUser;
        SOCKET _currentSocket;
        
    };
}