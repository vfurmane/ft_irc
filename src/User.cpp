#include "User.hpp"

User::User(const std::string &name): _name(name)
{
}

User::User(const User &obj): _name(obj._name)
{
}

User	&User::operator=(const User &rhs)
{
	this->_name = rhs._name;
	return (*this);
}

User::~User(void)
{
}

const std::string &User::getName(void) const
{
	return this->_name;
}
