#include <iostream>
#include <exception>
#include "Configuration.hpp"
#include "TCP/Server.hpp"

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

	TCP::Server serv(conf.getStrPort());
	serv.listen();
	return 0;
}
