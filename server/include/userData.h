#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../src/message.cpp"
#include "../src/privateUserData.cpp"

namespace Messanger
{
	class UserData : public PrivateUserData
	{
	public:
		UserData();
		UserData(const std::string& login, const std::string& password);
		
		
		std::map<std::string, std::vector<Message>>& getMessages();


		void setLogin(const std::string& login);
		void setPassword(const std::string& password);


		void addMessage(const std::string& receiver, const Message& mes);

	private:

		std::map<std::string, std::vector<Message>> _messages;
		
	};
}