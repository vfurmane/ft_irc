#include <iostream>
#include <exception>
#include "Configuration.hpp"
#include "Server.hpp"

int	main(int argc, char **argv)
{
	Configuration conf;

	try 
	{
		conf.parse_arguments(argc, argv);
	}
	catch (std::exception &e) 
	{
		std::cerr << "error: " << e.what() << std::endl;
		return 1;
	}

	Server serv(conf.getStrPort());
	try
	{
		serv.listen();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
