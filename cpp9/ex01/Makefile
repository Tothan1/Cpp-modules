NAME        = RPN
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -g
SRC_FILES   = main.cpp \
		RPN.cpp
OBJ_FILES   = $(SRC_FILES:.cpp=.o)
all: ${NAME}


${NAME} : ${OBJ_FILES}
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o ${NAME}

%.o: %.cpp
	@${CXX} ${CXXFLAGS} $(INC) -c $< -o $@

clean:
	@rm -f ${OBJ_FILES}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re  
