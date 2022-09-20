FROM ubuntu:22.04

RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends \
		make \
		gcc \
		clang \
	; \
	rm -r /var/lib/apt/lists/*;
