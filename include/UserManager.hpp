#ifndef USERMANAGER_HPP
# define USERMANAGER_HPP

# include <string>
# include <map>
# include <utility>

class Peer;
class User;

class UserManager
{
	public:
		typedef std::map<std::string, User>::iterator		iterator;
		typedef std::map<std::string, User>::const_iterator	const_iterator;

		UserManager(void);
		UserManager(const UserManager &obj);
		UserManager	&operator=(const UserManager &rhs);
		~UserManager(void);

		User	&operator[](const std::string &username);

		iterator	begin(void);
		iterator	end(void);
		const_iterator begin(void) const;
		const_iterator end(void) const;
		std::pair<UserManager::iterator, bool>	add(const User &user);
		void	remove(const User &user);

	private:
		std::map<std::string, User>	_users;
};

# include "Peer.hpp"
# include "User.hpp"

#endif
