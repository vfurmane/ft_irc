#include "UserManager.hpp"

UserManager::UserManager(void): _users()
{
}

UserManager::UserManager(const UserManager &obj): _users(obj._users)
{
}

UserManager	&UserManager::operator=(const UserManager &rhs)
{
	this->_users = rhs._users;
	return (*this);
}

UserManager::~UserManager(void)
{
}
