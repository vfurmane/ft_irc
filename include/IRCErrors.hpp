#ifndef IRCERRORS_HPP
# define IRCERRORS_HPP

#include <exception>
#include <string>

struct ERR_NONICKNAMEGIVEN : public std::exception
{
	static const int code = 431;
	virtual const char* what() const throw()
	{
		return ":No nickname given";
	}
};

struct ERR_NEEDMOREPARAMS : public std::exception
{
	std::string _str;
	ERR_NEEDMOREPARAMS(const std::string &command) : _str(command + " :Not enough parameters") {}
	~ERR_NEEDMOREPARAMS(void) throw() {}
	static const int code = 461;
	virtual const char* what() const throw()
	{
		return this->_str.c_str();
	}
};

struct ERR_ALREADYREGISTERED : public std::exception
{
	static const int code = 462;
	virtual const char* what() const throw()
	{
		return ":Unauthorized command (already registered)";
	}
};

#endif
