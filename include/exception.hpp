#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <exception>
#include <string>

class sysCallError : public std::exception {
	private:
		std::string _str;

	public:
		sysCallError(const std::string &syscall, const std::string &str) : _str(syscall + ": " + str) {}
		~sysCallError(void) throw() {}
		virtual const char* what() const throw()
		{
			return this->_str.c_str();
		}
};

struct InvalidChannelName : public std::exception
{
	virtual const char* what() const throw()
	{
		return "invalid channel name";
	}
};

#endif
