FROM irc_build

RUN set -eux; \
	apt-get update; \
	apt-get install -y \
		tcpdump; \
	rm -r /var/lib/apt/lists/*;

COPY docker-entrypoint.sh .

ENTRYPOINT ["./docker-entrypoint.sh"]
