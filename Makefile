NAME = minishell
HEADER = mini_shell.h
SRC = ./execution/env.c ./execution/execution.c ./execution/tools_list.c \
	./execution/utilise_blt1.c ./execution/utilise2.c ./execution/utilise3.c ./execution/herdoc.c \
	./execution/utilise_blt.c ./execution/utilise.c ./execution/utilise1.c ./execution/utilise4.c\
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./execution/utilise5.c \
	./parsing/change_var_ulit.c  ./parsing/set_speace_line.c ./parsing/get_in_out.c \
	./parsing/change_var.c ./parsing/check_errors.c ./parsing/get_args2.c \
	./parsing/change_var_one.c ./parsing/clear_list.c ./parsing/get_files.c ./parsing/set_list.c \
	./parsing/split_pip.c ./parsing/check_errors_var.c ./parsing/split_args.c ./execution/mini_shell.c \
	./parsing/wildcards.c ./parsing/wildcards_one.c ./parsing/wildcards_tow.c ./parsing/quote.c

OBJS = $(SRC:.c=.o)
READLINE = -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib
CFLAGS = -Wall -Wextra -Werror
OREAD =  -I/goinfre/$(USER)/homebrew/opt/readline/include
LIBS =  -L./libft -lft
RM = rm -f
CC = cc
Debugs = -g -fsanitize=address

all: libft $(NAME)

libft:
	@make all -C ./libft
	@make bonus -C ./libft

$(NAME) : $(OBJS)
	@$(CC)  $(CFLAGS) $(LIBS) $(READLINE) $(OBJS) -o $(NAME)
%.o : %.c $(HEADER) 
	$(CC) $(CFLAGS) $(OREAD) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft

re : fclean all

.PHONY: libft
