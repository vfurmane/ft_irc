#include "utils.hpp"

char	toIRCLower(char c)
{
	if (c >= 'A' && c <= ']')
		return c + 32;
	if (c == '~')
		return '^';
	return c;
}
