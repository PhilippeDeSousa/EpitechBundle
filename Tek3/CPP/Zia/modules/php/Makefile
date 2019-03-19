NAME 		= 	phpmodule.so

SRC 		=	PhpImplentation.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -W -Wall -fPIC -I ../../include -I ../../zia-api -std=c++17
LDFLAGS 	= -shared -fPIC

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
