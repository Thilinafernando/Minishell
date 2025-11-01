CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I/usr/include -Ilibft -Iget_next_line -Ilibprintf -Ireadline

PRINTDIR = libprintf/
PRINT = $(PRINTDIR)libftprintf.a

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

NAME = minishell

GNL = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c

EXECDIR = execution/
EXEC = execution/exec_cdion_pt2.c exec_conditions.c exec_child.c exec_parent.c exec_pt2.c ft_execution.c \
		ft_intergration.c ft_intergration2.c exec_utilss.c \

REDDIR = redirections/
RED = redirections/redirections.c heredoc.c heredoc_utils.c heredoc_utils2.c ftt_expansion.c\

UTILSDIR = Utils/
UTILS = Utils/refresh_redirections.c ft_signal.c utils_pipe.c ft_pipe.c free.c \
		testing_utils.c testing_utils2.c dollar.c export_utils.c export_utils2.c unset_utils.c\

SRCDIR = built-ins/
SRC = built-ins/ft_pwd.c ft_env.c ft_cd.c ft_export.c ft_unset.c ft_echo.c \
		ft_exit.c \

PARSDIR = parssing/
PRC = parssing/quote_processing.c syntax.c token_handlers.c token_utils.c tokenizer_core.c utils.c variable_expansion.c minishell.c \
		minishell_utils.c \

ALL_SRC = $(SRC) $(PRC) $(EXEC) $(UTILS) $(RED)

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))
GNL_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(GNL_SRC:.c=.o)))

all: $(NAME)

#bonus: $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJECTS) $(GNL_OBJECTS) $(PRINT)
	@echo "Compiling MINISHELL..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(GNL_OBJECTS) -o $(NAME) $(LIBFT) $(PRINT) -lreadline -lncurses

# Libft compiling
$(LIBFT): $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR) bonus --quiet
	@$(MAKE) -C $(LIBFTDIR) --quiet

$(OBJ_DIR)/%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(PARSDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(EXECDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(REDDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(UTILSDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

#PRINTF compiling
$(PRINT): $(PRINTDIR)
	@$(MAKE) -C $(PRINTDIR) --quiet

# GNL
$(OBJ_DIR)/%.o: $(GNL)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(MAKE) fclean -C $(PRINTDIR)
	rm -rf $(NAME)

re: fclean all

vall: all clean
		valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=/home/ilmahjou/fix_all/minishit/minshit/readline.supp ./minishell

.PHONY: all bonus clean fclean re

