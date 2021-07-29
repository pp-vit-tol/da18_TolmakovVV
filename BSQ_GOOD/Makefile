HDR		= include 
CFLAGS	= -Wall -Wextra -Werror -I $(HDR)
BIN		= bsq
SRC		= src
OBJ		= obj
HDRS	= $(wildcard $(HDR)/*.h)
SRCS	= $(wildcard $(SRC)/*.c)
OBJS	= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all:		$(BIN)

$(BIN):		$(HDRS) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o:	$(SRC)/%.c | $(OBJ)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
			mkdir -p $(OBJ)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(BIN)

re:			fclean all


.PHONY:		all clean fclean re
