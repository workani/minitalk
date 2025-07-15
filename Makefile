CC := cc
CC_FLAGS := -Wall -Wextra 	-Werror
RM := rm -f
INCLUDE = -I include

LIBFT := libft
LIBFT_ARCHIVE := $(LIBFT)/libft.a

SRC_DIR = src/

CLIENT = client
SERVER = server
SRC_CLIENT = $(addprefix $(SRC_DIR), $(CLIENT).c)
SRC_SERVER = $(addprefix $(SRC_DIR), $(SERVER).c)

OBJ_CLIENT = ${SRC_CLIENT:.c=.o}
OBJ_SERVER = ${SRC_SERVER:.c=.o}

all: $(LIBFT_ARCHIVE) $(CLIENT) $(SERVER)

$(LIBFT_ARCHIVE): 
	@make -C $(LIBFT)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CC_FLAGS) $(INCLUDE) $(SRC_CLIENT) $(LIBFT_ARCHIVE) -o $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CC_FLAGS) $(INCLUDE) $(SRC_SERVER) $(LIBFT_ARCHIVE)  -o $(SERVER)

clean: 
	@make clean -C $(LIBFT)
	$(RM) $(OBJ_CLIENT)
	$(RM) $(OBJ_SERVER)

fclean: clean
	@make fclean -C $(LIBFT)
	$(RM) $(CLIENT)
	$(RM) $(SERVER)

re: fclean all

.PHONY: all clean fclean re