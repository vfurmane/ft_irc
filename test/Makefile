NAME = test.out
SRCS = main.cpp Configuration.test.cpp ../src/Configuration.cpp handlers.test.cpp ../src/handlers.cpp ../src/IRCPeer.cpp ../src/TCPPeer.cpp IRCMessage.test.cpp ../src/IRCMessage.cpp
OBJS = $(SRCS:.cpp=.o)
CXX = c++
CPPFLAGS += $(addprefix -I, . ../include)
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
