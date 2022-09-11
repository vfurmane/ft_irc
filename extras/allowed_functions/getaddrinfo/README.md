# Showip

> Inspired from the 'Beej's Guide to Network Programming Using Internet Sockets' 

A program using the `getaddrinfo` function to get IP addresses associated to a hostname.

## How does it work?

The program expects a single parameter, the `hostname` to query.

We set the `hints` parameter to query the hostname for both IPv4 and IPv6, and we limit the results to socket streams.

```c
struct addrinfo hints;
int status;

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

status = getaddrinfo(argv[1], NULL, &hints, &res)
```

Finally, we iterate through the returned linked list.

```c
for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
	// printing the IP addresses...
}
```