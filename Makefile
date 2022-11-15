NAME		= libftprintf.a

SRCS	= \
		  srcs/ft_printf.c \
		  srcs/ft_vprintf.c \
		  srcs/ft_asprintf.c \
		  srcs/ft_printf_parse.c \
		  srcs/ft_printf_getarg.c \
		  srcs/ft_printf_putarg.c \
		  srcs/ft_printf_putint.c \
		  srcs/ft_printf_putuint.c \
		  srcs/ft_printf_putchar.c \
		  srcs/ft_printf_putstr.c \
		  srcs/ft_printf_putptr.c \
		  srcs/ft_printf_getwritten.c \
		  srcs/ft_printf_sanitize.c \
		  srcs/ft_printf_utils.c \
		  srcs/ft_printf_lltoa.c \

ASMSRCS		= \

LIB_NAMES	= \
			  libft \

HEADERS		= \
			  includes \

LIBS		= $(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes)

OBJS		= ${SRCS:.c=.o} $(ASMSRCS:.asm=.o)
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
DEPS		= ${SRCS:.c=.d}
DEPS_BONUS	= ${SRCS_BONUS:.c=.d}
CC			= cc
CCWFLGS		= -Wall -Wextra -Werror
CCDBGFLGS	= 
CCO1FLGS	= -O1 -march=native
CCO2FLGS	= -O2 -march=native
CCO3FLGS	= -O3 -march=native
DEPSFLAGS	= -MMD -MP
RM			= rm -f
MAKE		= make -C
AR			= ar
ARFLAGS		= rcs
NASM		= nasm
NASMFLAGS	= -felf64

.PHONY: all clean fclean re bonus

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(AR) $(ARFLAGS) $(NAME) $(OBJS)
		#$(CC) $(CCWFLGS) $(CCDBGFLGS) -I$(HEADERS) -o $(NAME) $(OBJS) $(LIB_LD) $(LIBS)

bonus : $(OBJS) $(OBJS_BONUS)
		$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS)

$(LIB_PATHS) :
		$(MAKE) $(dir $@)

all : $(NAME)

clean :
		-$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)

fclean : clean
		-$(RM) $(NAME)

re : fclean all

%.o : %.asm Makefile
		$(NASM) $(NASMFLAGS) -o $@ $<

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCWFLGS) $(CCDBGFLGS) $(DEPSFLAGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@
