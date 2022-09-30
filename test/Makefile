NAME = test.out
SRCS = main.cpp commands.test.cpp Configuration.test.cpp Message.test.cpp PeerManager.test.cpp Peer.test.cpp Server.test.cpp $(addprefix commands/, nick.test.cpp quit.test.cpp user.test.cpp)
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
