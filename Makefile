# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 16:51:51 by aguiot--          #+#    #+#              #
#    Updated: 2019/01/18 16:51:52 by aguiot--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minitalk
SERVER		= server
CLIENT		= client
CC				= clang

# Compiler & Preprocessor flags
CFLAGS		+= -Wall -Werror -Wextra
CPPFLAGS	+= -I libft/ -I include/

# Recompile on headers/Makefile changes
DEPS			= libft/libft.h include/minitalk.h Makefile

# Source files
SRC_PATH				= src/
SRC_SERVER_NAME	= server utils
SRC_CLIENT_NAME	= client utils
SRC_SERVER			= $(addsuffix .c, $(SRC_SERVER_NAME))
SRC_CLIENT			= $(addsuffix .c, $(SRC_CLIENT_NAME))

# Object files
OBJ_PATH				= obj/
OBJ_SERVER_NAME	= $(addsuffix .o, $(SRC_SERVER_NAME))
OBJ_CLIENT_NAME	= $(addsuffix .o, $(SRC_CLIENT_NAME))
OBJ_SERVER			= $(addprefix $(OBJ_PATH), $(OBJ_SERVER_NAME))
OBJ_CLIENT			= $(addprefix $(OBJ_PATH), $(OBJ_CLIENT_NAME))

# Library
LIB_PATH	= libft
LIB_NAME	= ft
LIB_FILE	= $(LIB_PATH)/lib$(LIB_NAME).a
LIB_FLAGS	= -L $(LIB_PATH) -l $(LIB_NAME)

# Colors
C_RESET		= \033[0m
C_PENDING	= \033[0;36m
C_SUCCESS	= \033[0;32m

# Escape Sequences (ANSI/VT100)
ES_ERASE	= "\033[A\033[K\033[A"
ERASE			= $(ECHO) $(ES_ERASE)

# Hide STD/ERR and prevent Make from returning non-zero code
HIDE_STD	= > /dev/null
HIDE_ERR	= 2> /dev/null || true

# Multi platforms 
ECHO 			= echo
ifeq ($(shell uname),Linux)
	ECHO		+= -e
endif

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(LIB_FILE) $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LIB_FLAGS) -o $(SERVER)
	@$(ERASE)
	@$(ERASE)
	@$(ECHO) "$(NAME):$(SERVER)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(CLIENT): $(LIB_FILE) $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LIB_FLAGS) -o $(CLIENT)
	@$(ERASE)
	@$(ERASE)
	@$(ECHO) "$(NAME):$(CLIENT)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(LIB_FILE):
	@echo ""
	@$(MAKE) -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) $(HIDE_ERR)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_PENDING)⏳ $(C_RESET)]"
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@$(ERASE)

clean:
	@$(RM) -r $(OBJ_PATH) $(HIDE_ERR)
	@$(RM) -r $(NAME).dSYM $(HIDE_ERR)
	@$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	@$(RM) $(SERVER) $(CLIENT)
	@$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: clean fclean all re
