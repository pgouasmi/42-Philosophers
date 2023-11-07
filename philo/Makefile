# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:47:49 by pgouasmi          #+#    #+#              #
#    Updated: 2023/11/07 11:44:01 by pgouasmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLOR
_GREEN = \033[92m
_YELLOW = \033[33m
_RED = \033[31m

#POLICE
_END = \033[0m
_BOLD = \033[1m

OS = $(shell uname)

NAME = philo
CFLAGS = -Wall -Wextra -Werror -IIncludes -ggdb3
RM = @rm -rf
CC = @cc
DIR = @mkdir -p
PRINT = @echo
HEADER = Includes/philo.h
# NORM = @norminette | awk '$$NF!="OK!" {print "$(_RED)" $$0 "\033[0;0m"}'
FILES = philo\
		Initialization/struct_init\
		Initialization/struct_init_utils\
		Utils/ft_atoi\
		Free/free_struct
		
OBJS = $(addsuffix .o, $(addprefix Objects/, $(FILES)))

$(NAME): $(OBJS)
ifeq ($(OS),Linux)
	# $(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	# $(NORM)
	# $(PRINT) "${_BOLD}Norminette done.${_END}"
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) $(OBJS) -o $(NAME)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"
else
	$(PRINT) "This $(NAME) was made for Linux only.\a\n"
endif

Objects/%.o: Sources/%.c Makefile $(HEADER)
ifeq ($(OS),Linux)
	$(DIR) Objects Objects/Initialization Objects/Utils Objects/Free
	$(PRINT) "Compiling ${_BOLD}$<$(_END)..."
	$(CC) -c $(CFLAGS) $< -o $@
else
	$(PRINT) "This $(NAME) was made for Linux only.\a"
endif

all: $(NAME)

clean:
	$(PRINT) "\n${_BOLD}Cleaning Objects...${_END}"
	$(RM) .OS
	$(RM) $(OBJS)
	$(PRINT) "${_BOLD}${_GREEN}Objects cleaned.\a${_END}"

fclean:
	$(PRINT) "\n${_RED}Cleaning Objects...${_END}"
	$(RM) $(OBJS)
	$(PRINT) "${_RED}Deleting Objects directory...${_END}"
	$(RM) Objects
	$(PRINT) "${_RED}Deleting $(NAME)...${_END}"
	$(RM) $(NAME)
	$(RM) .OS
	$(PRINT) "${_GREEN}Objects cleaned.${_END}"
	$(PRINT) "${_GREEN}Objects directory deleted.${_END}"
	$(PRINT) "${_GREEN}$(NAME) deleted.\a\n${_END}"

re: fclean all

norminette:
	$(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	$(NORM)
	$(PRINT) "${_BOLD}Norminette done.${_END}"

force:

.PHONY: all clean fclean re norminette force