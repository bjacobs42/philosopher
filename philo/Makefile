NAME		:= philo
SRC_FR		:= ./src/
OBJ_FR		:= ./obj/
INCLUDES	:= ./include/
CC			:= cc

# Reset
NC		:= \033[0m# 		Text Reset

# Regular Colors
BLACK	:= \033[0;30m#	Black
RED		:= \033[3;31m#	Red
GREEN	:= \033[3;32m#	Green
BLD_GRN	:= \033[1;32m#	Green but bold
YELLOW	:= \033[3;33m#	Yellow
BLUE	:= \033[1;34m#	Blue
PURPLE	:= \033[3;35m#	Purple
BLD_PUR	:= \033[1;35m#	Purple but bold
CYAN	:= \033[3;36m#	Cyan
WHITE	:= \033[1;37m#	White

ifdef WITH_DEBUG
CFLAGS	:= -g -fsanitize=address
else
CFLAGS	:= -Wall -Werror -Wextra -I
endif

INIT_FR	:= initialization/
INIT_FILES	:= $(INIT_FR)init_functions.c $(INIT_FR)init_philosophers.c

MISC_FR	:= misc/
MISC_FILES	:= $(MISC_FR)ft_atoi.c $(MISC_FR)parsing.c $(MISC_FR)put_error.c $(MISC_FR)utils.c

SRC_FILES	:= main.c announcer.c destroy.c monitor.c routine.c $(INIT_FILES) $(MISC_FILES)
SRCS		:= $(addprefix $(SRC_FR), $(SRC_FILES))
OBJS		:= $(addprefix $(OBJ_FR), $(SRC_FILES:.c=.o))

all: ${NAME}

$(OBJ_FR)%.o : ${SRC_FR}%.c | $(OBJ_FR)
	@echo "$(PURPLE)Compiling... $(NC)🧱 $(PURPLE) $< $(NC)"
	@${CC} ${CFLAGS} $(INCLUDES) -c $^ -o $@

$(OBJ_FR):
	@echo "$(YELLOW)Creating folders... $(NC)🗂"
	@mkdir -p $(OBJ_FR)$(INIT_FR) $(OBJ_FR)$(MISC_FR)

$(NAME): ${OBJS}
	@echo "$(BLD_GRN)Building... 🏗$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@
	@echo "$(BLD_GRN)Done! 🏠$(NC)"

clean:
	@echo "$(CYAN)Cleaning...$(NC) 🧹"
	@rm -rf ${OBJ_FR}

fclean: clean
	@echo "$(RED)Destroying...$(NC) 💥"
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
