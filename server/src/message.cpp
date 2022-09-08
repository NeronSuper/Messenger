#include "../include/message.h"

namespace Messanger
{
	Message::Message()
	{
		_data = {};
	}


	Message::Message(const std::string& login, const std::string &message)
		: _data(login, message)  
	{
	}

	Message::Message(const Message& copy)
		: _data(copy._data)
	{
	}

	const std::string& Message::getOwner() const
	{
		return _data.first;
	}

	const std::string& Message::getMess() const
	{
		return _data.second;
	}
}