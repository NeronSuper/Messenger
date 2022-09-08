#pragma once
#include <string>

namespace Messanger
{
	class PrivateUserData
	{
	public:
		PrivateUserData();
		PrivateUserData(const std::string& login, const std::string& password);

		const std::string& getLogin() const;
		const std::string& getPassword() const;

		void setLogin(const std::string& login);
		void setPassword(const std::string& password);

	private:
		std::pair<std::string, std::string> _pData; 

		
	};
}
