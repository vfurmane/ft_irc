NAME = ircserv
SRCS = $(addprefix src/, main.cpp ChannelManager.cpp Channel.cpp commands.cpp utils.cpp Configuration.cpp IRCReplies.cpp Peer.cpp PeerManager.cpp Message.cpp Server.cpp User.cpp UserManager.cpp $(addprefix commands/, cap.cpp invite.cpp join.cpp kick.cpp list.cpp mode.cpp names.cpp notice.cpp nick.cpp part.cpp pass.cpp ping.cpp quit.cpp topic.cpp user.cpp whois.cpp $(addprefix notice/, channel.cpp nickname.cpp) $(addprefix privmsg/, channel.cpp nickname.cpp) privmsg.cpp $(addprefix mode/, channel.cpp $(addprefix channel/, invite_only.cpp key.cpp operator.cpp topic.cpp))))
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
