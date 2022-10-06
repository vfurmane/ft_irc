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

User	&UserManager::operator[](const std::string &username)
{
	return this->_users.at(username);
}

UserManager::iterator	UserManager::begin(void)
{
	return this->_users.begin();
}

UserManager::iterator	UserManager::end(void)
{
	return this->_users.end();
}

UserManager::const_iterator	UserManager::begin(void) const
{
	return this->_users.begin();
}

UserManager::const_iterator	UserManager::end(void) const
{
	return this->_users.end();
}
