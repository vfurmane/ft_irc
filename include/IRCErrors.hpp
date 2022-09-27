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

#endif
