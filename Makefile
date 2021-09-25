# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 14:51:42 by rotrojan          #+#    #+#              #
#    Updated: 2021/09/26 00:35:39 by rotrojan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =						main.c											\
	arrow_keys.c			cursor_utils.c		ft_getch.c					\
	get_cursor_pos.c		getterm.c			init_term.c					\
	set_termios.c			special_keys.c									\
	exit_shell.c			ft_dsleep.c			ft_fflush.c					\
	ft_gethostname.c		getbinpath.c 		path.c						\
	set_timeout.c			signals.c										\
	env_utils.c				ft_getenv.c			ft_inenv.c					\
	ft_setenv.c				ft_unsetenv.c									\
	input.c					prompt.c 			shell.c 					\
	inchar.c				inchar_utils.c		insert_inchar.c				\
	get_history.c			history_get_down.c	history_get_up.c			\
	history_utils.c			init_history.c		put_in_history.c			\
	lexer.c					tok_redirections.c	tok_separators.c			\
	tok_utils.c				tok_word.c										\
	build_ast.c				free_ast.c			parse_logical_operator.c	\
	parse_parenthesis.c		parse_pipeline.c	parse_simple_cmd.c			\
	token_identifiers.c														\
	expand_vars.c			expansions_utils.c	fill_new_arg.c				\
	perform_expansions.c	realloc_argv.c									\
	remove_quotes.c			utils.c											\
	exec_ast.c				exec_compound_cmd.c	exec_pipe.c					\
	exec_simple_cmd.c		exit_value.c		run_binary.c				\
	run_builtin.c															\
	heredoc.c				input_redirection.c	output_redirection.c		\
	redirection.c															\
	cd.c					echo.c				env.c						\
	exit.c					export.c			export_display_env.c		\
	pwd.c					unset.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = sources
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes)

LIBS = gc ft

MAKE = make
MAKEFLAGS += --no-print-directory
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra -Werror
ifeq ($(DEBUG), on)
	CFLAGS += -g3 -fsanitize=address
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%) -lncurses

vpath %.c	$(addprefix $(SRCS_DIR),						\
				$(addprefix /system, /. /env)				\
				$(addprefix /shell, /. /history /inchar)	\
				$(addprefix /execution, /. /redirection)	\
				/. /terminal /lexer /parser /builtins /expansions)

all: libs
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) libft/libft.a libgc/libgc.a
	@printf '\nlinking %s\n' '$@'
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@cat .ascii_art

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR)
	@printf '\r\033[K\033[33mcompiling minishell:\033[0m %s' '$@'
	@$(CC) $(CFLAGS)  $(INCLUDES_DIR:%=-I %) -c $< -o $@

$(OBJS_DIR):
	@$(MKDIR) $@

libs:
	@$(MAKE) -C libft
	@$(MAKE) -C libgc

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	@$(RM) $(OBJS_DIR)/debug*
	@touch $@

clean:
	@$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	@$(RM) $(NAME)
	@printf 'minishell removed\n'

re: fclean all

.PHONY: all clean fclean re libs
