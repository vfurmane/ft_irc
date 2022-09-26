#ifndef IRCERRORS_HPP
# define IRCERRORS_HPP

#include <exception>
#include <string>

class ERR_UNKNOWNCOMMAND : public std::exception
{
	private:
		const std::string	_str;

	public:
		static const int code = 421;
		ERR_UNKNOWNCOMMAND(const std::string &command) : _str(command + " :Unknown command") {}
		~ERR_UNKNOWNCOMMAND(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

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

struct ERR_UMODEUNKNOWNFLAG : public std::exception
{
	static const int code = 501;
	virtual const char* what() const throw()
	{
		return ":Unknown MODE flag";
	}
};

#endif
