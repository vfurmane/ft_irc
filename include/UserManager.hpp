#ifndef USERMANAGER_HPP
# define USERMANAGER_HPP

# include <string>
# include <map>
# include <utility>
# include "Manager.hpp"

class Peer;
class User;

class UserManager : public Manager<std::string, User>
{
	public:
		UserManager(void);
		UserManager(const UserManager &obj);
		UserManager	&operator=(const UserManager &rhs);
		~UserManager(void);

		User	&add(const User &user);
		void	remove(const User &user);
};

# include "Peer.hpp"
# include "User.hpp"

#endif
