#include "Configuration.hpp"

Configuration::Configuration() : _parsed(false), _port(), _password()
{
}

Configuration::Configuration(const Configuration &obj)
{
	*this = obj;
}

Configuration::~Configuration(void)
{

}

Configuration	&Configuration::operator=(const Configuration &rhs)
{
	this->_parsed = rhs._parsed;
	this->_port = rhs._port;
	this->_str_port = rhs._str_port;
	this->_password = rhs._password;
	return *this;
}

uint16_t	Configuration::parse_port_number(const char *str)
{
	int		port = 0;
	size_t	lead_zeros_i = 0;
	bool	leading_zeros = true;

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (lead_zeros_i >= 5)
			throw NotAPortNumber();
		if (leading_zeros && str[i] == '0') 
			continue;
		leading_zeros = false;
		if (str[i] < '0' || str[i] > '9')
			throw NotAPortNumber();
		lead_zeros_i++;
	}
	std::istringstream(str) >> port;
	if (port < 1 || port > 65535)
		throw NotAPortNumber();
	return port;
}

void	Configuration::parse_arguments(int argc, char **argv)
{
	if (this->_parsed)
		throw AlreadyParsed();
	if (argc != 3)
		throw NotEnoughArguments();

	_port = parse_port_number(argv[1]);
	_str_port = argv[1];
	_password = argv[2];
}


uint16_t		Configuration::getPort(void) const
{
	return this->_port;
}

char			*Configuration::getStrPort(void) const
{
	return this->_str_port;
}

const std::string		&Configuration::getPassword(void) const
{
	return this->_password;
}
