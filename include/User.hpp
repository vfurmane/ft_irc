#ifndef USER_HPP
# define USER_HPP

#include <string>

class User
{
	public:
		User(const std::string &name);
		User(const User &obj);
		User &operator=(const User &rhs);
		~User(void);
	
	private:
		std::string	_name;
};

#endif
