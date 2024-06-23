NAME	:= philo_bonus
OBJ_DIR	:= obj/
SRC_DIR	:= src/
INCLUDE	:= -I include
CC		:= cc

# Reset
NC		:= \033[0m# 	Text Reset

# Regular Colors
BLACK	:= \033[0;30m#	Black
RED		:= \033[0;31m#	Red
GREEN	:= \033[1;32m#	Green
YELLOW	:= \033[1;33m#	Yellow
BLUE	:= \033[1;34m#	Blue
PURPLE	:= \033[0;35m#	Purple
BLD_PUR	:= \033[1;35m#	Purple but bold
CYAN	:= \033[1;36m#	Cyan
WHITE	:= \033[1;37m#	White

ifdef WITH_DEBUG
CFLAGS	:= -g -fsanitize=address
else
CFLAGS	:= -Wall -Werror -Wextra
endif

INIT_DIR	:= initialization/
INIT_FILES	:= $(INIT_DIR)init_functions_bonus.c $(INIT_DIR)init_philosophers_bonus.c

MISC_DIR	:= misc/
MISC_FILES	:= $(MISC_DIR)ft_atoi_bonus.c $(MISC_DIR)parsing_bonus.c $(MISC_DIR)put_error_bonus.c $(MISC_DIR)utils_bonus.c \
			   $(MISC_DIR)ft_strjoin_bonus.c $(MISC_DIR)ft_itoa_bonus.c

FILES		:= main_bonus.c destroy_bonus.c monitor_bonus.c routine_bonus.c $(INIT_FILES) $(MISC_FILES)
SRC_FILES	:= $(addprefix $(SRC_DIR), $(FILES))
OBJ_FILES	:= $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo "$(RED)compiling:$(NC)" "$(BLUE)$^$(NC)"
	@$(CC) $(INCLUDE) $(CFLAGS) $(NLXFM) -c $^ -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)creating folders..."
	@mkdir -p $@
	@mkdir -p $@/$(INIT_DIR)
	@mkdir -p $@/$(MISC_DIR)

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	@echo "$(PURPLE)============================[$(NC)$(BLD_PUR)$(NAME)$(NC)$(PURPLE)]============================$(NC)"
	@echo "$(YELLOW)creating $@..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(INCLUDE) -o  $@
	@echo "$(GREEN)done!$(NC)"

debug:
	make WITH_DEBUG=1 all

clean:
	@echo "$(CYAN)cleaning...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
