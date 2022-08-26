#include "baseApp.cpp"





auto main()->int
{
	Messanger::BaseApp *baseApp = Messanger::BaseApp::instance();
	
	baseApp->start();

	return 0;
}