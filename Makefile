NAME = ircserv
SRCS = $(addprefix src/, main.cpp ChannelManager.cpp Channel.cpp commands.cpp utils.cpp Configuration.cpp IRCReplies.cpp Peer.cpp PeerManager.cpp Message.cpp Server.cpp User.cpp UserManager.cpp $(addprefix commands/, cap.cpp join.cpp mode.cpp nick.cpp part.cpp pass.cpp ping.cpp quit.cpp user.cpp $(addprefix privmsg/, channel.cpp nickname.cpp) privmsg.cpp quit.cpp user.cpp $(addprefix mode/, channel.cpp $(addprefix channel/, invite_only.cpp key.cpp operator.cpp))))
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
