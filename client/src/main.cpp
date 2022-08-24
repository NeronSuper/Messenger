#include "baseApp.cpp"





auto main()->int
{
	BaseApp *baseApp = BaseApp::instance();
	
	baseApp->start();

	return 0;
}