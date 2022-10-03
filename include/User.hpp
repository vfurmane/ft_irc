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

		const std::string	&getName(void) const;
	
	private:
		std::string	_name;
};

#endif
