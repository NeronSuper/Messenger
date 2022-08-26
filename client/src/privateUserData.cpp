#include "../include/privateUserData.h"

namespace Messanger
{
	PrivateUserData::PrivateUserData()
	{
		_pData = {};
	}

	PrivateUserData::PrivateUserData(const std::string& login, const std::string& password)
		: _pData(login, password)
	{
	}

	const std::string& PrivateUserData::getLogin() const
	{
		return _pData.first;
	}

	const std::string& PrivateUserData::getPassword() const
	{
		return _pData.second;
	}

	void PrivateUserData::setLogin(const std::string& login)
	{
		_pData.first = login;
	}

	void PrivateUserData::setPassword(const std::string& password)
	{
		_pData.second = password;
	}
}