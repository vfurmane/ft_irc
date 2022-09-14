#include <iostream>
#include <exception>
#include "Configuration.hpp"

int	main(int argc, char **argv)
{
	Configuration conf;

	try {
		conf.parse_arguments(argc, argv);
	} catch (std::exception &e) {
		std::cerr << "error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
