# GENERAL SETTINGS ====================================================================
NAME = minishell
LIB_NAME = libft
.SILENT:

# DIRECTORIES==========================================================================
DIR_SRC		:= sources/
DIR_INC 	:= includes/
DIR_BUILD	:= .build/

DIR_LIB		:= $(LIB_NAME)/
DIR_INC_LIB	:= $(DIR_LIB)includes/

# FLAGS & COMPILATOR SETTINGS =========================================================
CC 			:= cc
DEPS_FLAGS	:= -MMD -MP
WARN_FLAGS	:= -Wall -Werror -Wextra 
C_FLAGS		:= $(WARN_FLAGS) $(DEPS_FLAGS)
INC_FLAGS	:= -I $(DIR_INC) -I $(DIR_INC_LIB)
LIB_FLAGS	:= -L $(DIR_LIB) -lft


COMP 		:= $(CC) $(C_FLAGS) $(INC_FLAGS) -g3
LINK		:= $(LIB_FLAGS) -lreadline

ANTI_RELINK	:= Makefile $(DIR_INC) $(DIR_INC_LIB) 

# FUNCTIONS ===========================================================================
define generate_var_sources_dir
DIR_$(1) = $(addprefix $(DIR_SRC), $(shell echo $(1) | tr '[:upper:]' '[:lower:]')/)
endef

define generate_var_sources
SRC_$(1) = $(addprefix $(DIR_$(1)),$(F_$(1)))
endef

define generate_var_objects
OBJS_$(1) = $(patsubst $(DIR_SRC)%.c,$(DIR_BUILD)%.o,$(SRC_$(1)))
endef

define generate_var_deps
DEPS_$(1) = $(patsubst $(DIR_SRC)%.c,$(DIR_BUILD)%.d,$(SRC_$(1)))
endef

# FUNCTIONS ===========================================================================
TOTAL_FILES		=	$(words $(OBJS))
CURRENT_FILE	:=	0
BAR_LENGTH		:=	50

define draw_progress_bar
	@printf "\r$(CYAN)$(BOLD)Compiling $(NAME): $(RESET)["
	@n=$(CURRENT_FILE); \
	total=$(TOTAL_FILES); \
	pct=`expr $$n '*' 100 / $$total`; \
	fill=`expr $$n '*' $(BAR_LENGTH) / $$total`; \
	empty=`expr $(BAR_LENGTH) - $$fill`; \
	printf "$(GREEN)%*s$(RESET)" $$fill "" | tr ' ' '='; \
	printf "%*s" $$empty "" | tr ' ' ' '; \
	if [ $$n -eq $$total ]; then \
		printf "] $(BLUE)$(BOLD)%3d%%$(RESET) (%d/%d)" $$pct $$n $$total; \
	else \
		printf "] $(BOLD)%3d%%$(RESET) (%d/%d)" $$pct $$n $$total; \
	fi; \
	if [ $$n = $$total ]; then printf "\n"; fi
endef

# COLORS ==============================================================================
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

# COMPONENTS ==========================================================================
COMPONENTS :=			PARSING 			\
						LEXING 				\
						CHECKING 			\
						TOKEN_FORMATTING	\
						STYLE				\
						UTILS				\
						HEREDOC				\
						EXEC				\
						ENV					\
						BUILTINS			\
						DEBUG				\
						SIGNALS				\

# FILES ===============================================================================
F_MAIN :=				main.c				\

F_SIGNALS :=			signals.c			\

F_LEXING :=				tokenize_input.c	\
						tokenize_word.c		\
						tokenize_operator.c	\
						tokenize_quote.c	\
			
F_CHECKING :=			is_valid_input.c	\
						is_quote.c			\
						is_whitespace.c		\
						is_operator.c		\
						check_syntax_error.c\

F_PARSING :=			get_input.c			\
						parse_input.c		\
						format_input.c		\

F_EXEC :=				exec_cmd.c			\
						exec_launcher.c		\
						exec_process.c		\
						path_utils.c		\
						utils.c				\
						pipes_utils.c		\
						exec_builtin.c		\
						redir_builtin.c		\
						error_utils.c		\
						redir_simple_cmd.c	\
						check_sig_child.c	\

F_ENV 	:=				env_array_to_list.c	\
						get_env_value.c		\
						find_env_var.c		\
						env_list_to_array.c \

F_HEREDOC	:=			handle_heredoc.c	\
						gen_heredoc_filename.c \
						
F_UTILS :=				init_struct.c		\
						clear_token.c		\
						clear_env_list_elem.c	\
						dup_token.c			\
						create_token.c		\
						exit_minishell.c	\
						countocc.c			\
						str_patdel.c		\
						str_chardel.c		\
						str_patreplace.c	\
						str_replace.c		\
						extract_var_key.c	\
						exp_var_strlen.c	\
						ft_tabdup.c			\
						ft_tablen.c			\
						gen_random_num_sequence.c \
						clear_hd_filename_elem.c \
						clear_var_vector.c	\
						lstgetprev.c		\
						safe_close.c		\
						unlink_free_tmpfile.c	\
						quoted_arg_len.c	\
						
F_TOKEN_FORMATTING :=	format_tokens.c		\
						format_command.c	\
						format_redir.c		\
						format_env_var.c	\

F_STYLE :=				welcome.c 			\
						build_prompt.c		\

F_BUILTINS :=			ft_echo.c 			\
						ft_cd.c				\
						ft_pwd.c			\
						ft_export.c			\
						ft_unset.c			\
						ft_exit.c			\
						ft_env.c			\

F_DEBUG :=				print_input.c		\
						print_tab.c			\
						print_heredoc.c 	\
						print_exec.c		\


# VARS GENERATION =====================================================================
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_sources_dir,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_sources,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_objects,$(comp))))
$(foreach comp,$(COMPONENTS),$(eval $(call generate_var_deps,$(comp))))

OBJS := $(foreach comp, $(COMPONENTS), $(OBJS_$(comp))) \
		$(DIR_BUILD)main.o

DEPS := $(foreach comp, $(COMPONENTS), $(DEPS_$(comp))) \
		$(DIR_BUILD)main.d

# COMPILATION =========================================================================
$(NAME) : $(OBJS)
	@printf "$(BLUE)$(BOLD)[INFO]$(RESET) $(WHITE)Linking objects...$(RESET)\n"
	$(COMP) $^ -o $@ $(LINK)
	@printf "$(GREEN)$(BOLD)[SUCCESS]$(RESET) $(WHITE)Build successful!$(RESET) Created $(BOLD)$(CYAN)$(NAME)$(RESET)\n"

$(DIR_BUILD) :
	@mkdir -p $(DIR_BUILD)

$(DIR_BUILD)%.o : $(DIR_SRC)%.c $(ANTI_RELINK) | $(DIR_BUILD)
	@mkdir -p $(dir $@)
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(call draw_progress_bar)
	$(COMP) -c $< -o $@
	@if [ $(CURRENT_FILE) = $(TOTAL_FILES) ]; then echo; fi

-include $(DEPS)

# RULES ===============================================================================
# build -------------------------------------------------------------------------------
all : lib $(NAME)

lib :
	@make -s -C $(DIR_LIB)

# clean -------------------------------------------------------------------------------
clean:
	@printf "$(ORANGE)$(BOLD)[CLEAN]$(RESET) $(WHITE)Cleaning object files from $(CYAN)$(NAME)$(RESET)...\n"
	@make -s clean -C $(DIR_LIB)
	@rm -rf $(DIR_BUILD)

fclean: 
	@make -s fclean -C $(DIR_LIB)
	@printf "$(ORANGE)$(BOLD)[CLEAN]$(RESET) $(WHITE)Cleaning object files from $(CYAN)$(NAME)$(RESET)...\n"
	@rm -rf $(DIR_BUILD)
	@printf "$(ORANGE)$(BOLD)[CLEAN]$(RESET) $(WHITE)Removing executables...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)$(BOLD)[DONE]$(RESET) $(WHITE)Clean complete!$(RESET)\n"

re: fclean all

.DEFAULT_GOAL = all

# debug -------------------------------------------------------------------------------
print-%:
	@echo $($(patsubst print-%,%,$@))

.PHONY: all lib clean fclean re print-%
