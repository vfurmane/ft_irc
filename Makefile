NAME = ircserv
SRCS = $(addprefix src/, main.cpp commands.cpp Configuration.cpp Peer.cpp PeerManager.cpp Message.cpp Server.cpp $(addprefix commands/, nick.cpp quit.cpp user.cpp))
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
INCLDIR = include
CXX = c++
CPPFLAGS += -MMD $(addprefix -I, $(INCLDIR))
CXXFLAGS += -Wall -Wextra -Werror --std=c++98
RM = rm -f

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS)
	$(RM) -r $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
