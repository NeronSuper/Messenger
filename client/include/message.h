#pragma once
#include <string>
#include <ctime>

//#pragma warning(disable: 4996)
class Message
{
public:
	Message();
	Message(const Message& copy);
	Message(const std::string&,	const std::string&);

	const std::string& getMessage() const;
	const std::string& getLogin() const;
	const tm &getTime() const;

	void setLogin(std::string &login);
	void setMessage(std::string&& message);
	void setDt(tm &dt);


private:
	std::pair<std::string, std::string> _data;
	std::tm* _dt;
};

