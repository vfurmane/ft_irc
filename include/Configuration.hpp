#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

# include <exception>
# include <iostream>
# include <string>
# include <stdint.h>

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

		uint16_t		getPort(void) const;
		char			*getStrPort(void) const;

	private:
		bool		_parsed;
		uint16_t	_port;
		char		*_str_port;
		std::string	_password;
};

#endif
