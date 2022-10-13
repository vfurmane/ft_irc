#!/bin/sh

tcpdump -A -qq port 6667 &

exec "$@" > /dev/null 2>&1
