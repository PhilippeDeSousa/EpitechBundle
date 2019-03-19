NAME 		= 	sslmodule.so

SRC 		=	SSLModule.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -W -Wall -fPIC -I ../../include -I ../../zia-api -std=c++17
LDFLAGS 	= -shared -fPIC
LDLIBS		= -lcrypto -lssl

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
