NAME		= libftprintf.a

CCDEFS		= \

SRCS		= \
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
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/)

CCDEFSFLGS	= $(foreach def,$(CCDEFS),-D $(def))

BUILDDIR	= build
OBJS		= $(SRCS:%.c=$(BUILDDIR)/%.o) $(ASMSRCS:%.s=$(BUILDDIR)/%.o)
DEPS		= $(SRCS:%.c=$(BUILDDIR)/%.d)
CC			= cc
CCWFLGS		= -Wall -Wextra -Werror
CCDBGFLGS	= -fsanitize=address -g
CCO1FLGS	= -O1 -march=native
CCO2FLGS	= -O2 -march=native
CCO3FLGS	= -O3 -march=native
DEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir
AR			= ar
ARFLAGS		= rcs
NASM		= nasm
NASMFLAGS	= -felf64

all : $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		cp libft/libft.a ./libftprintf.a
		$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus : $(NAME)

test : $(BUILDDIR) $(LIB_PATHS) $(OBJS) main.o
		$(CC) $(CCWFLGS) -o test $(OBJS) $(BUILDDIR)/main.o

$(LIB_PATHS) :
		$(MAKE) $(dir $@)

clean :
		-$(RM) $(BUILDDIR)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

$(BUILDDIR)/%.o : %.s Makefile
		mkdir -p $(@D)
		$(NASM) $(NASMFLAGS) -o $(BUILDDIR)/$@ $<

-include $(DEPS)

$(BUILDDIR)/%.o : %.c Makefile
		mkdir -p $(@D)
		$(CC) $(CCWFLGS) $(DEPSFLAGS) $(CCDEFSFLGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

.PHONY: all clean fclean re bonus

