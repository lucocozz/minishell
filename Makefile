# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 16:53:41 by rotrojan          #+#    #+#              #
#    Updated: 2021/04/30 21:40:12 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
NAME = minishell

SRCS = main.c
SRCS_DIR = sources
OBJS_DIR = .objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)
INCLUDES_DIR = includes $(LIBS:%=lib%/includes)
LIBS = ft
CC = clang
RM = rm -f
MKDIR = mkdir -p

CFLAGS = -MMD -Wall -Wextra -Werror

CXXFLAGS = $(INCLUDES_DIR:%=-I %)
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%) -lncurses

vpath %.c $(SRCS_DIR) $(SRCS_DIR)/system
vpath %.h $(INCLUDES_DIR)
vpath %.a $(LIBS:%=lib%)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)

$(NAME): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(NAME) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB))
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re
