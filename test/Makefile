NAME = test.out
SRCS = main.cpp Channel.test.cpp ChannelManager.test.cpp commands.test.cpp utils.test.cpp Configuration.test.cpp IRCReplies.test.cpp Manager.test.cpp Message.test.cpp PeerManager.test.cpp Peer.test.cpp Server.test.cpp User.test.cpp UserManager.test.cpp $(addprefix commands/, cap.test.cpp invite.test.cpp join.test.cpp kick.test.cpp list.test.cpp mode.test.cpp names.test.cpp nick.test.cpp notice.test.cpp part.test.cpp pass.test.cpp ping.test.cpp whois.test.cpp $(addprefix notice/, channel.test.cpp nickname.test.cpp) $(addprefix privmsg/, channel.test.cpp nickname.test.cpp) privmsg.test.cpp quit.test.cpp topic.test.cpp user.test.cpp $(addprefix mode/, channel.test.cpp $(addprefix channel/, invite_only.test.cpp key.test.cpp operator.test.cpp topic.test.cpp)))
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
INCLDIR = include
CXX = c++
CPPFLAGS += -MMD $(addprefix -I, $(INCLDIR)) $(addprefix -I, . ../include) -DNDEBUG
CXXFLAGS += -Wall -Wextra -Werror --std=c++11
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
