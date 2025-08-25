# GENERAL SETTINGS ====================================================================
NAME = minishell
LIB_NAME = libft
# .SILENT:

# DIRECTORIES==========================================================================
DIR_SRC		:= sources/
DIR_INC 	:= includes/
DIR_BUILD	:= .build/

DIR_LIB		:= $(LIB_NAME)/
DIR_INC_LIB	:= $(DIR_LIB)includes/

# FLAGS & COMPILATOR SETTINGS =========================================================
CC 			:= cc
DEPS_FLAGS	:= -MMD -MP
WARN_FLAGS	:= -Wall -Wextra -Werror -g3
C_FLAGS		:= $(WARN_FLAGS) $(DEPS_FLAGS)
INC_FLAGS	:= -I $(DIR_INC) -I $(DIR_INC_LIB)
LIB_FLAGS	:= -L $(DIR_LIB) -lft


COMP 		:= $(CC) $(C_FLAGS) $(INC_FLAGS)
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

# COMPONENTS ==========================================================================
COMPONENTS			:=	PARSING 					\
						LEXING						\
						CHECKING					\
						TOKEN_FORMATTING			\
						STYLE						\
						UTILS						\
						HEREDOC						\
						DEBUG						\
						EXEC						\
						ENV							\
						BUILTINS					\
						SIGNALS						\

# FILES ===============================================================================

F_CHECKING			:=	check_syntax_error.c		\
						is_operator.c				\
						is_quote.c					\
						is_valid_input.c			\
						is_whitespace.c				\

F_ENV				:=	env_array_to_list.c			\
						env_list_to_array.c			\
						find_env_var.c				\
						get_env_value.c				\

F_DEBUG				:=	print_input.c				\
						print_tab.c					\
						print_heredoc.c				\
						print_exec.c				\

F_EXEC				:=	start_exec.c				\
						exec_cmd.c					\
						create_files_in_block.c		\
						clear_exec.c				\
						wait_child.c				\
						is_builtin.c				\
						init_block_cmd.c			\
						prepare_redir.c				\
						handle_builtin.c			\


F_HEREDOC			:=	gen_heredoc_filename.c		\
						handle_heredoc.c			\

F_LEXING			:=	tokenize_input.c			\
						tokenize_operator.c			\
						tokenize_quote.c			\
						tokenize_word.c				\

F_PARSING			:=	get_input.c					\
						parse_input.c				\

F_SIGNALS 			:=	signals.c					\
						signal_utils.c				\

F_UTILS				:=	cd_utils.c					\
						clear_env_list_elem.c		\
						clear_hd_filename_elem.c 	\
						clear_v_token.c				\
						clear_var_vector.c			\
						close_fd_exec.c				\
						count_blocks.c				\
						count_command_args.c		\
						count_valid_tokens.c		\
						countocc.c					\
						create_token.c				\
						dup_token.c					\
						exit_minishell.c			\
						exp_var_strlen.c			\
						extract_var_key.c			\
						extract_var_value.c			\
						ft_tabdup.c					\
						ft_tablen.c					\
						gen_random_num_sequence.c	\
						get_cmd_path.c				\
						handle_absolute_path.c		\
						init_struct.c				\
						is_empty_env_var_token.c	\
						is_redir_object_token.c		\
						is_executable_token.c		\
						lstgetprev.c				\
						ptr_replace.c				\
						quoted_arg_len.c			\
						remove_token_if.c			\
						safe_close.c				\
						safe_free.c					\
						str_chardel.c				\
						str_patdel.c				\
						str_patreplace.c			\
						str_replace.c				\
						unlink_free_tmpfile.c		\
						close_and_swap.c			\
						ft_close.c					\

F_TOKEN_FORMATTING	:=	format_tokens.c				\
						format_command.c			\
						format_redir.c				\
						format_env_var.c			\

F_STYLE				:=	welcome.c 					\
						build_prompt.c				\

F_BUILTINS			:=	ft_echo.c 					\
						ft_cd.c						\
						ft_pwd.c					\
						ft_export.c					\
						ft_unset.c					\
						ft_exit.c					\
						ft_env.c					\

F_MAIN				:=	main.c						\

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
	$(COMP) $^ -o $@ $(LINK)

$(DIR_BUILD) :
	mkdir -p $(DIR_BUILD)

$(DIR_BUILD)%.o : $(DIR_SRC)%.c $(ANTI_RELINK) | $(DIR_BUILD)
	mkdir -p $(dir $@)
	$(COMP) -c $< -o $@

-include $(DEPS)

# RULES ===============================================================================
# build -------------------------------------------------------------------------------
all : lib $(NAME) inputrc

lib :
	make -C $(DIR_LIB)

inputrc:
	@echo "set colored-stats on" > ~/.inputrc
	@echo "set completion-ignore-case on" >> ~/.inputrc

# clean -------------------------------------------------------------------------------
clean:
	make clean -C $(DIR_LIB)
	@rm -rf $(DIR_BUILD)

fclean:
	make fclean -C $(DIR_LIB)
	rm -rf $(DIR_BUILD)
	rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL = all

# debug -------------------------------------------------------------------------------
print-%:
	@echo $($(patsubst print-%,%,$@))


.PHONY: all lib clean fclean re print-% inputrc
