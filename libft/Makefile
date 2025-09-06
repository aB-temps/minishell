#-------------------------------- VARIABLES ----------------------------------#
NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar rcs
RM		=	rm -f

#-------------------------------- DIRECTORIES --------------------------------#
INCLUDE_DIR		=	includes
LIST_DIR		=	./src/list/
UTILS_DIR		=	./src/utils/
LIST_DB_CIR_DIR	=	./src/list_db_cir/
CHAR_DIR		=	./src/char/
STRING_DIR		=	./src/string/
IO_DIR			=	./src/io/
MEMORY_DIR		=	./src/memory/
ADVANCE_DIR		=	./src/advance/
VECTOR_DIR		=	./src/vectors/
BUILD_DIR		=	.build/

#-------------------------------- SOURCE FILES -------------------------------#

LIST_SRCS			=	ft_lstadd_front.c ft_lstlast.c \
						ft_lstadd_back.c ft_lstsize.c \
						ft_lstdelone.c ft_lstclear.c \
						ft_lstiter.c ft_lstmap.c \
						ft_lstnew.c

UTILS_SRCS			=	free_tab.c

LIST_DB_CIR_SRCS	=	ft_lstadd_back_db_cir.c ft_lstsize_db_cir.c \
						ft_lstclear_db_cir.c \
						ft_lstnew_db_cir.c ft_lstadd_front_db_cir.c

CHAR_SRCS			=	ft_isalpha.c ft_isdigit.c ft_isascii.c \
						ft_isprint.c ft_isalnum.c ft_toupper.c \
						ft_tolower.c

STRING_SRCS			=	ft_strlen.c ft_strchr.c ft_strrchr.c \
						ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
						ft_strncmp.c ft_strjoin.c ft_str_free_to_join.c \
						ft_strtrim.c ft_strmapi.c ft_striteri.c \
						ft_strdup.c ft_substr.c ft_strndup.c ft_strcmp.c

IO_SRCS				=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
						ft_putnbr_fd.c print_digit.c print_pointer.c

MEMORY_SRCS			=	ft_memset.c ft_bzero.c ft_memcpy.c \
						ft_memchr.c ft_memcmp.c ft_memmove.c \
						ft_calloc.c

ADVANCE_SRCS		=	ft_atoi.c ft_split.c ft_itoa.c \
						get_next_line.c ft_printf.c ft_atoi_long.c

VECTOR_SRCS			=	add_element.c clear_vector.c \
						create_vector.c grow_vector.c

SRCS				=	$(addprefix $(LIST_DIR), $(LIST_SRCS)) \
						$(addprefix $(UTILS_DIR), $(UTILS_SRCS)) \
						$(addprefix $(LIST_DB_CIR_DIR), $(LIST_DB_CIR_SRCS)) \
						$(addprefix $(CHAR_DIR), $(CHAR_SRCS)) \
						$(addprefix $(STRING_DIR), $(STRING_SRCS)) \
						$(addprefix $(IO_DIR), $(IO_SRCS)) \
						$(addprefix $(MEMORY_DIR), $(MEMORY_SRCS)) \
						$(addprefix $(ADVANCE_DIR), $(ADVANCE_SRCS)) \
						$(addprefix $(VECTOR_DIR), $(VECTOR_SRCS)) \


#-------------------------------- OBJECTS ------------------------------------#
OBJS			=	$(patsubst %.c,$(BUILD_DIR)%.o,$(SRCS))
DEPENDENCIES	=	$(OBJS:.o=.d)


#-------------------------------- COLORS -------------------------------------#

BLACK		:=	\033[38;2;0;0;0m
RED			:=	\033[38;2;178;34;34m
GREEN		:=	\033[38;2;60;179;113m
BLUE		:=	\033[38;2;30;144;255m
YELLOW		:=	\033[38;2;255;215;0m
MAGENTA		:=	\033[38;2;186;85;211m
CYAN		:=	\033[38;2;0;206;209m
WHITE		:=	\033[38;2;230;230;230m
ORANGE		:=	\033[38;2;255;140;0m
PURPLE		:=	\033[38;2;147;112;219m
RESET		:=	\033[0m
BOLD		:=	\033[1m

#-------------------------------- RULES --------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)


$(BUILD_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -MMD -MP -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

print-%:
	@echo $($(patsubst print-%,%,$@))

-include $(DEPENDENCIES)

.PHONY: all clean fclean re print-%
