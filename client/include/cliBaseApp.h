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

		void sendMessage();
		void lookAtChat();
		void printMessages(const std::string& chat);

    private:
        BaseApp* _baseApp;
        UserData* _currentUser;
        SOCKET _ServerSocket;
        
    };
}