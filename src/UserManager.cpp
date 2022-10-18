#include "UserManager.hpp"

UserManager::UserManager(void): Manager()
{
}

UserManager::UserManager(const UserManager &obj): Manager(obj)
{
}

UserManager	&UserManager::operator=(const UserManager &rhs)
{
	(void)rhs;
	return (*this);
}

UserManager::~UserManager(void)
{
}

User	&UserManager::add(const User &user)
{
	return Manager::add(user.peer.getFd(), user);
}

void	UserManager::remove(const int fd)
{
	Manager::remove(fd); 
}

void UserManager::remove(const User &user)
{
	this->remove(user.peer.getFd());
}

User	&UserManager::getByNickname(const std::string &nick)
{
	for (UserManager::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->second.peer.getNickname() == nick)
			return it->second;
	}
	throw std::out_of_range("UserManager::getByNickname");
}

bool	UserManager::hasByNickname(const std::string &nick)
{
	for (UserManager::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->second.peer.getNickname() == nick)
			return true;
	}
	return false;
}
