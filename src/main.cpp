#include <iostream>
#include <exception>
#include "Configuration.hpp"
#include "TCPServer.hpp"

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

	TCPServer serv(conf.getStrPort());
	serv.listen();
	return 0;
}
