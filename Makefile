SRCS	= \
			srcs/ft_asprintf.c \
			srcs/ft_printf.c \
			srcs/ft_printf_parse.c \
			srcs/ft_vprintf.c \
			srcs/ft_printf_sanitize.c \
			srcs/ft_printf_getarg.c \
			srcs/ft_printf_putarg.c \
			srcs/ft_printf_lltoa.c \
			srcs/ft_printf_getwritten.c \
			srcs/ft_printf_utils.c \

LIBS	=	-lft \

HEADERS	=	includes/

LIB_NAMES	= $(subst -l,lib,$(LIBS))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(lib).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
CC			= gcc
CCFLAGS		= -Wall -Wextra -g
DEPSFLAGS	= -MMD -MP
NAME		= libft_printf.a
RM			= rm -f
MAKE		= make -C
WRAP		=
AR			= ar
AR_FLAGS	= rc

.PHONY: all clean fclean re

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(AR) $(AR_FLAGS) $(NAME) $(OBJS)
		#$(CC) $(CCFLAGS) -I$(HEADERS) $(LIB_HEADERS) -o $(NAME) $(OBJS) $(LIB_LD) $(LIBS)

$(LIB_PATHS) :
		$(MAKE) $(notdir $(basename $@))

all : $(NAME)

clean :
		-$(RM) $(OBJS) $(DEPS)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCFLAGS) $(DEPSFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@ $(LIB_LD) $(LIBS)
