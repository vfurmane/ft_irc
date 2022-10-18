#ifndef USERMANAGER_HPP
# define USERMANAGER_HPP

# include <string>
# include <map>
# include <utility>
# include "Manager.hpp"

class Peer;
class User;

class UserManager : public Manager<int, User>
{
	public:
		UserManager(void);
		UserManager(const UserManager &obj);
		UserManager	&operator=(const UserManager &rhs);
		~UserManager(void);

		User	&add(const User &user);
		void	remove(const int fd);
		void	remove(const User &user);
		User	&getByNickname(const std::string &nick);
		bool	hasByNickname(const std::string &nick);
};

# include "User.hpp"

#endif
