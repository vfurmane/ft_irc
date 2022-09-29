NAME = test.out
SRCS = main.cpp Configuration.test.cpp ../src/Configuration.cpp Message.test.cpp ../src/Message.cpp ../src/Peer.cpp ../src/Server.cpp ../src/PeerManager.cpp ../src/commands.cpp $(addprefix ../src/commands/, nick.cpp quit.cpp user.cpp)
OBJS = $(SRCS:.cpp=.o)
CXX = c++
CPPFLAGS += $(addprefix -I, . ../include) -DNDEBUG
CXXFLAGS += -Wall -Wextra -Werror --std=c++11
RM = rm -f

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
