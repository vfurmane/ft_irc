/*
 * From the 'Beej's Guide to Network Programming Using Internet Sockets'
 *
 * Show IP addresses for a host given on the command line
 * Usage: showip hostname
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int	main(int argc, char **argv) {
	struct addrinfo hints, // the getaddrinfo hints parameter
					*res; // the getaddrinfo result
	int status;          // the getaddrinfo returned status

	// arguments check
	if (argc != 2) {
		fprintf(stderr, "usage: %s hostname\n", argv[0]);
		return 1;
	}

	// set the hints parameter
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // get both IPv4 and IPv6
	hints.ai_socktype = SOCK_STREAM; // get only socket streams

	// call the getaddrinfo function
	// lookup on the hostname given in parameter
	// no service needed
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res))) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	printf("IP addresses for %s:\n\n", argv[1]);
	for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
		char ipstr[INET6_ADDRSTRLEN]; // the stringified ip address
		void *addr;                  // the raw address buffer
		char *ipver;                // the version of the IP address (IPv4 or IPv6)

		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr); // stringify the raw address
		printf("\t%s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res);
	return 0;
}
