SRCS =	srcs/ft_asprintf.c \
		srcs/ft_printf.c \
		srcs/ft_printf_parse.c \
		srcs/ft_vprintf.c \
		srcs/ft_printf_sanitize.c \
		srcs/ft_printf_getarg.c \
		srcs/ft_printf_putarg.c \
		srcs/ft_printf_lltoa.c \
		srcs/ft_printf_getwritten.c \
		srcs/ft_printf_utils.c \

LIBS =	-lft \

HEADERS = includes/

LIB_NAMES	= $(subst -l,lib,$(LIBS))
LIB_DIRS	= $(foreach lib,$(LIB_NAMES),libs/$(lib))
LIB_DIRS_LD = $(foreach libdir,$(LIB_DIRS),-L$(libdir)/lib)
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),libs/$(lib)/lib/$(lib).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-Ilibs/$(lib)/includes/)

OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
CC			= gcc
CCFLAGS		= -Wall -Wextra -g
DEPSFLAGS	= -MMD -MP
LIBDIR		= lib
NAME		= ft_printf.a
RM			= rm -Rf

.PHONY: all clean fclean re

$(NAME) : $(LIB_PATHS) $(OBJS) $(LIBDIR)
		ar rc $(LIBDIR)/$@ $(OBJS)
		#$(CC) $(CCFLAGS) -I$(HEADERS) $(LIB_HEADERS) -o $@ $(OBJS) $(LIB_DIRS_LD) $(LIBS)

$(LIB_PATHS) :
		make -C libs/$(notdir $(basename $@))

$(LIBDIR) :
		mkdir $(LIBDIR)

all : $(NAME)

clean :
		-$(RM) $(OBJS) $(DEPS)

fclean : clean
		make -C $(LIB_DIRS) fclean
		-$(RM) $(NAME)
		-$(RM) $(LIBDIR)

re : fclean all

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCFLAGS) $(DEPSFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@ $(LIB_DIRS_LD) $(LIBS)
