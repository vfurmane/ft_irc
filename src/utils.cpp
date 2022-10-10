#include "utils.hpp"

const char	*CRLF = "\r\n";

char	toIRCLower(char c)
{
	if (c >= 'A' && c <= ']')
		return c + 32;
	if (c == '~')
		return '^';
	return c;
}

std::string	toIRCLower(const std::string &str)
{
	std::string	lowercase_str;

	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
		lowercase_str += toIRCLower(*it);;
	return lowercase_str;
}
