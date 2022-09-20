[![Compilation](https://github.com/vfurmane/ft_irc/actions/workflows/compilation.yml/badge.svg)](https://github.com/vfurmane/ft_irc/actions/workflows/compilation.yml) [![Tests](https://github.com/vfurmane/ft_irc/actions/workflows/tests.yml/badge.svg)](https://github.com/vfurmane/ft_irc/actions/workflows/tests.yml)

# ft_irc

## Build

The main project and tests are buildable using the `make` command.

You can also use the *Dockerfile* as follows:

```sh
docker build -t irc_build .

# Project
docker run -it -v $PWD:$PWD --workdir $PWD irc_build make
docker run -it -v $PWD:$PWD --workdir $PWD irc_build ./ircserv <port> <password>

# Tests
docker run -it -v $PWD:$PWD --workdir $PWD irc_build make -C test
docker run -it -v $PWD:$PWD --workdir $PWD irc_build ./test/test.out
```

## Contributors

- [@ppiques](https://github.com/ppiques)
- [@tvogel](https://github.com/tvogel)
- [@vfurmane](https://github.com/vfurmane)
