#ifndef USERMANAGER_HPP
# define USERMANAGER_HPP

# include <map>
# include "User.hpp"

class UserManager
{
	public:
		typedef std::map<int, User>::iterator	iterator;
		typedef std::map<int, User>::const_iterator	const_iterator;

		UserManager(void);
		UserManager(const UserManager &obj);
		UserManager	&operator=(const UserManager &rhs);
		~UserManager(void);

		User	&operator[](int fd);

		iterator	begin(void);
		iterator	end(void);
		const_iterator begin(void) const;
		const_iterator end(void) const;

	private:
		std::map<int, User>	_users;
};

#endif
