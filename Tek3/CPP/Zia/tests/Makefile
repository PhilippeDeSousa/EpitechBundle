NAME = tests_run

CC	= clang++

SRCS	= src/CBufferTests.cpp
SRCS	+= ../src/CBuffer.cpp
SRCS	+= ../src/SharedModules.cpp
SRCS	+= ../src/SharedObject.cpp

OBJS	= $(SRCS:.cpp=.o)

RM	= rm -f

CFLAGS = -Wall -Wextra -pedantic -std=c++17
CFLAGS += -I ../Catch2/ -I ../include -I ../zia-api

LDLIBS = -ldl -lstdc++fs -lpthread

GREEN	= '\033[0;32m'
NO_COLOR	= '\033[0m'

%.o : %.cpp
	@$ $(CC) $(CFLAGS) -c $< -o $@
	@echo "$(CC) $(CFLAGS) -c $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .cpp

all: $(NAME)

$(NAME): $(OBJS)
	@$ $(CC) $(OBJS) $(LDLIBS) -o $@
	@echo "$(CC) $(OBJS) $(LDLIBS) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"
	./$@

debug: CFLAGS += -g3
debug: re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME:.so=.a)

re: fclean all

.PHONY: all clean fclean re debug
