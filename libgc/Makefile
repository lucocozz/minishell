NAME= 	libgc.a

GC= 	gc_exit.c			get_garbage_lst.c		gc_malloc.c			\
		gc_free.c			gc_free_all.c			gc_utils.c


SRCS=	$(GC)
OBJS= $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR= .objs
DEPENDENCIES= $(OBJS:%.o=%.d)

MAKE = make
MAKEFLAGS += --no-print-directory
CC= clang
MKDIR= mkdir -p
RM= rm -f

CFLAGS= -Wall -Wextra -Werror -MMD
CXXFLAGS= -I includes

vpath %.c sources 

all: $(NAME)

$(NAME): $(OBJS)
	@printf '\narchiving %s\n' '$@'
	@ar -rcs $(NAME) $(OBJS)
	@printf '\033[33m\033[1m%s done\n\033[0m' '$@'

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@printf '\r\033[K\033[33mcompiling libgc:\033[0m %s' '$@'
	@$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	@$(MKDIR) $(OBJS_DIR)

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@printf 'libgc removed\n'

re: fclean all

.PHONY: all clean fclean re
