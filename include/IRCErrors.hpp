#ifndef IRCERRORS_HPP
# define IRCERRORS_HPP

#include <exception>
#include <string>

struct AIRCError : std::exception
{
	virtual const char* what() const throw() = 0;
};

class ERR_NOSUCHCHANNEL : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NOSUCHCHANNEL(const std::string &command) : _str("403 " + command + " :No such channel") {}
		~ERR_NOSUCHCHANNEL(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_UNKNOWNCOMMAND : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_UNKNOWNCOMMAND(const std::string &command) : _str("421 " + command + " :Unknown command") {}
		~ERR_UNKNOWNCOMMAND(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

struct ERR_NONICKNAMEGIVEN : public AIRCError
{
	virtual const char* what() const throw()
	{
		return "431 :No nickname given";
	}
};

struct ERR_ERRONEUSNICKNAME : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_ERRONEUSNICKNAME(const std::string &nick) : _str("432 " + nick + " :Erroneous nickname") {}
		~ERR_ERRONEUSNICKNAME(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

struct ERR_NICKNAMEINUSE : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NICKNAMEINUSE(const std::string &nick) : _str("433 " + nick + " :Nickname is already in use") {}
		~ERR_NICKNAMEINUSE(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_NEEDMOREPARAMS : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NEEDMOREPARAMS(const std::string &command) : _str("461 " + command + " :Not enough parameters") {}
		~ERR_NEEDMOREPARAMS(void) throw() {}
		virtual const char* what() const throw()
	{
		return this->_str.c_str();
	}
};

class ERR_BADCHANNELKEY : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_BADCHANNELKEY(const std::string &channel) : _str("475 " + channel + " :Cannot join channel (+k)") {}
		~ERR_BADCHANNELKEY(void) throw() {}
		virtual const char* what() const throw()
	{
		return this->_str.c_str();
	}
};

struct ERR_ALREADYREGISTRED : public AIRCError
{
	virtual const char* what() const throw()
	{
		return "462 :Unauthorized command (already registered)";
	}
};

struct ERR_UMODEUNKNOWNFLAG : public AIRCError
{
	virtual const char* what() const throw()
	{
		return "501 :Unknown MODE flag";
	}
};

#endif
