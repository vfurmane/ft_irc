#ifndef IRCERRORS_HPP
# define IRCERRORS_HPP

#include <exception>
#include <string>

struct AIRCError : std::exception
{
	virtual const char* what() const throw() = 0;
};

class ERR_NOSUCHNICK : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NOSUCHNICK(const std::string &nickname) : _str("401 " + nickname + " :No such nick/channel") {}
		~ERR_NOSUCHNICK(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_NOSUCHCHANNEL : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NOSUCHCHANNEL(const std::string &channel) : _str("403 " + channel + " :No such channel") {}
		~ERR_NOSUCHCHANNEL(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_NORECIPIENT : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_NORECIPIENT(const std::string &command) : _str("411 :No recipient given (" + command + ")") {}
		~ERR_NORECIPIENT(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

struct ERR_NOTEXTTOSEND : public AIRCError
{
	virtual const char* what() const throw()
	{
		return "412 :No text to send";
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

class ERR_ERRONEUSNICKNAME : public AIRCError
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
		ERR_NICKNAMEINUSE(const std::string &nick) : _str("433 * " + nick + " :Nickname is already in use") {}
		~ERR_NICKNAMEINUSE(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_USERNOTINCHANNEL : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_USERNOTINCHANNEL(const std::string &nick, const std::string &channel) : _str("441 " + nick + " " + channel + " :They aren't on that channel") {}
		~ERR_USERNOTINCHANNEL(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_NOTONCHANNEL : public AIRCError
{
	private:
		const std::string _str;

	public:
		ERR_NOTONCHANNEL(const std::string &channel) : _str("442 " + channel + " :You're not on that channel") {}
		~ERR_NOTONCHANNEL(void) throw() {}
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

class ERR_KEYSET : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_KEYSET(const std::string &channel) : _str("467 " + channel + " :Channel key already set") {}
		~ERR_KEYSET(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};


class ERR_UNKNOWNMODE : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_UNKNOWNMODE(const std::string &mode, const std::string &channel) : _str("472 " + mode + " :is unknown mode char to me for " + channel) {}
		~ERR_UNKNOWNMODE(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

class ERR_CHANOPRIVSNEEDED : public AIRCError
{
	private:
		const std::string	_str;

	public:
		ERR_CHANOPRIVSNEEDED(const std::string &channel) : _str("482 " + channel + " :You're not a channel operator") {}
		~ERR_CHANOPRIVSNEEDED(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
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
