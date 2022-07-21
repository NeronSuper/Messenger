#pragma once
#include "cli.h"
#include "baseApp.h"

class CLImessage : public CLI
{
public:
	CLImessage();

	void sendMessage(std::string& receiver);
	void startNewChat();
	void showChat();

	void listOfChats();
	void openChat(std::string& chat);
	void help()override;

private:
	BaseApp* _baseApp;

};

