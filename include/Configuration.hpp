#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

# include <exception>
# include <iostream>
# include <string>
# include <sstream>
# include <stdint.h>

# define SERVER_VERSION "dev"

class Configuration
{
	public:
		Configuration(void);
		Configuration(const Configuration &obj);
		~Configuration(void);

		Configuration	&operator=(const Configuration &rhs);

		class NotEnoughArguments : public std::exception {
			virtual const char* what() const throw()
			{
				return "not enough arguments";
			}
		};

		class AlreadyParsed : public std::exception {
			virtual const char* what() const throw()
			{
				return "already parsed";
			}
		};

		class NotAPortNumber : public std::exception {
			virtual const char* what() const throw()
			{
				return "not a port number";
			}
		};

		static uint16_t	parse_port_number(const char *str);
		void			parse_arguments(int argc, char **argv);

		const std::string		&getNetworkName(void) const;
		const std::string		&getServerName(void) const;
		const std::string		&getServerVersion(void) const;
		const std::string		&getServerCreationDate(void) const;
		const std::string		&getUserModes(void) const;
		const std::string		&getChannelModes(void) const;
		uint16_t		getPort(void) const;
		char			*getStrPort(void) const;
		const std::string		&getPassword(void) const;
		
	private:
		const std::string	_network_name;
		const std::string	_server_name;
		const std::string	_server_version;
		const std::string	_server_creation_date;
		const std::string	_user_modes;
		const std::string	_channel_modes;
		bool				_parsed;
		uint16_t			_port;
		char				*_str_port;
		std::string			_password;
};

#endif
