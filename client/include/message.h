#pragma once
#include <string>

namespace Messanger
{
	class Message
	{
	public:
		Message();
		Message(const Message& copy);
		Message(const std::string&,	const std::string&);

		const std::string& getOwner() const;
		const std::string& getMess() const;


	private:
		std::pair<std::string, std::string> _data;

	};
}
