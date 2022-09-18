#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <exception>
#include <string>

struct sysCallError : public std::exception {
	std::string _str;
	sysCallError(const std::string &syscall, const std::string &str) : _str(syscall + ": " + str) {}
	~sysCallError(void) throw() {}
	virtual const char* what() const throw()
	{
		return this->_str.c_str();
	}
};

#endif
