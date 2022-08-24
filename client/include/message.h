#pragma once
#include <string>
#include <ctime>

class Message
{
public:
	Message();
	Message(const Message& copy);
	Message(const std::string&,	const std::string&);

	


private:
	std::pair<std::string, std::string> _data;

};

