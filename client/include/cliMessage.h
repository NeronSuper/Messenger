#pragma once
#include "cli.h"
#include "baseApp.h"

class CLImessage : public CLI
{
public:
	CLImessage();

	void sendMessage();
	void showChat();
	void help()override;

private:
	BaseApp* _baseApp;

};

