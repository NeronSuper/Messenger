#include "../include/message.h"
#include <sstream>

Message::Message()
{
	std::time_t t = std::time(0);   // get time now
	_dt = std::localtime(&t);
	_data = {};
}


Message::Message(const std::string& login, const std::string &message)
	: _data(login, message)  
{
	std::time_t t = std::time(0);   // get time now
	_dt = std::localtime(&t);
	
}

Message::Message(const Message& copy)
	: _data(copy._data), _dt(copy._dt)
{

}

const std::string& Message::getMessage() const
{
	return _data.second;
}

const std::string& Message::getLogin() const
{
	return _data.first;
}

const tm &Message::getTime()const
{
	return *_dt;
}

void Message::setLogin(std::string& login)
{
	_data.first = login;
}

void Message::setMessage(std::string&& message)
{
	_data.second = message;
}

void Message::setDt(tm &dt)
{
	
}



