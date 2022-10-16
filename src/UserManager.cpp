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
	return Manager::add(user.peer.getUsername(), user);
}

void	UserManager::remove(const std::string &username)
{
	Manager::remove(username); 
}

void UserManager::remove(const User &user)
{
	this->remove(user.peer.getUsername());
}
