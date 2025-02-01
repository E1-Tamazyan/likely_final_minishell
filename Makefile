DEFAULT =	\033[0m
GREEN   =	\033[32m
ORANGE = \033[38;5;214m
YELLOW = \033[38m;5;226m
DIM = \033[2m
BLUE    =       \033[34m
RED = \033[38;5;196m
INFO_B = \033[36m
INFO_Y = \033[38;5;226m
INFO_YD = \033[38;5;214m

CC = cc

NAME = minishell

READLINE = readline

LIBS_DIR = libraries

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include

CFLAGS = -g -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address

READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = minishell.h

# SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME =	main.c mini_utils.c \
			lib_utils.c lib_utils_1.c \
			lib_utils_2.c cmd_utils.c \
			sort_env.c initialization.c \
			checks.c token_utils.c \
			print_fts.c mini_utils_1.c \
			export.c builtin_utils.c \
			pwd.c echo.c cd.c unset.c \
			exit.c exit_utils.c \
			error_handle.c expand_dol.c\
			execution.c free.c pipe_utils.c\
			exec_utils.c pipe.c\
			signals.c status.c exec_utils_2.c\
			shlvl.c cmd.c remove_extra.c\
			lib_utils_3.c lib_utils_4.c \
			redir.c redir_utils.c\
			error.c\

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	@echo "${GREEN}Compiled $<.${DEFAULT}"
	@$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH) -lncurses > /dev/null

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null
	@echo "${INFO_Y}FYI: ${INFO_YD}Linking is in progress...${DEFAULT}"

$(LIBS_DIR)/$(READLINE):
	@echo "${INFO_B}Loading required libraries...${DEFAULT}"
	@./$(LIBS_DIR)/config_readline readline > /dev/null

clean:
	@echo "${DIM}Cleaning...${DEFAULT}"
	@$(RM) $(OBJS)
	@echo "${ORANGE}Done$(DEFAULT):)"

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(LIBS_DIR)/$(READLINE)
	@rm -rf $(OBJS_DIR)
	@make -s clean -C $(LIBS_DIR)/readline-8.2

config:
	mkdir -p readline_local
	./readline_config.sh readline_local

re: fclean all

.PHONY: all clean fclean re
