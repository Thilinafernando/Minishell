/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:42 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:11 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libprintf/ft_printf.h"
# include "get_next_line/get_next_line.h"

# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal_status;

typedef struct s_env {
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_info {
	char	***exec;
	int		pos;
	char	**env;
	char	**tmp;
	int		size;
	int		fd_in_out[2];
	int		cpipe[2];
	int		exit_status;
	int		fd_in_child;
	int		fd_out_child;
	char	*heredoc;
	pid_t	pids[128];
	int		pid_counts;
	int		prevpipe;
	int		mat;
	int		count;
	int		flag;
	char	*dollar;
	char	*line;
	int		*heredocs;
	int		heredocfd;
	int		flagheredoc;
	int		icount;
}	t_info;

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_HEREDOC,
	TOKEN_VAR,
	TOKEN_SPACE
}	t_token_type;

typedef struct s_token {
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_parse_ctx
{
	char			*input;
	int				*i;
	t_token			*head;
	t_token			**current_word_token;
	t_info			*info;
}	t_parse_ctx;

// built-ins / handle malloc fails and general errors
char	*ft_pwd(t_info *info);
void	err_cd(char *arg);
void	free_mat(char **matrix);
int		exisit(char **matrix, char *arg);
void	matrix_tmp(t_info *info);
int		ft_strcmp(const char *s1, const char *s2);
int		verify_equal(char *str);
void	form_env(char **env, t_info	*info);
void	print_pwd(t_info *info);
void	ft_unset(t_info *info, char **args);
void	ft_export(t_info *info, char **args);
void	ft_env(char **matrix, t_info *info);
void	ft_cd(char **args, t_info *info);
int		ft_echo(char **args, t_info *info);
void	ft_exit(char **args, t_info *info);
void	ft_pipe_exit(char **args, t_info *info);

// built-ins utils
int		verify(char	*str);
int		append(char **matrix, char *args);
void	process_join(t_info *info, char **args, char ***new);
char	**matrix_join(t_info *info, char **args, int size);
void	swap(char **a, char **b);
void	sorting(t_info *info);
void	err_unset(char *str);
int		verify_unset(char *str, t_info *info);
int		calcu(char **args, t_info *info);
int		dups(char **args);
int		yes_unset(t_info *info, char **args, int i);
void	save_redirections(t_info *info, t_token *token);
int		size_command(t_token **token);
void	copy_command(t_token **token, char ***matrix);

// redirections
int		ft_input(char **exec, t_info *info);
int		ft_output(char **exec, t_info *info);
int		ft_append(char **exec, t_info *info);
int		ft_heredoc(char **exec, t_info *info);
void	ctrl_c_here(int sig);

// Heredoc utils
char	*heredoc_filename(void);
void	err_fd_heredoc(char **filename);
void	err_heredoc_null(char **exec, char *str);
void	err_heredoc_pfd(t_info *info);
void	write_dollar(char **dollar, int fd);
void	heredoc_printing_fd(int fd, char *str);
int		parent_signal_handler(int *status, t_info *info);

// dollar
char	*mdollar(char *str, t_info *info);
char	*expand_dollar1(char *line, t_info *info);

// pipe and proccess
void	ft_execution(t_info *info);
void	close_fd(int *ar);
void	failure(int fd[2], t_info *info);
void	failure_command(int fd[2], char **str, t_info *info);
char	*abs_path(char *command, t_info *info);
char	*build_full(char *path, char *command);
char	**find_path(char **envp);
void	cd_home(t_info *info, char **home);
int		is_directory(const char *path);
int		builtout_re(char ***matrix, t_info *info);
int		is_builtin(char **matrix);
int		is_builtout(char ***matrix, t_info *info);
int		handle_builtin_redirection(char ***matrix, t_info *info, int mat);
int		is_only_redirection(char ***matrix, t_info *info);
void	block_only_rd(t_info *info);
void	block_rd(t_info *info);
void	one_exec(char **command, t_info *info, int fd[2]);
void	child_pt2(t_info *info);
void	child_pt1(t_info *info, int *i);
void	child_block(t_info *info, int *i);
int		ft_redirections(char **matrix, t_info *info);
int		is_redirection(char **matrix);
int		is_builtin(char **matrix);
void	exec_builtin(char **matrix, t_info *info);
int		builtout_process(char ***matrix, t_info *info, int mat);
void	parent_block(t_info *info, int *i, pid_t pid);
void	fail_wait(t_info *info);
void	wait_block(t_info *info);
void	process_count_blocks(char ***exec, int *i, int *count, int *cmd_rd);
int		count_exec_blocks(char ***exec);
void	init_exectution(t_info *info);
void	fork_block(t_info *info, pid_t *pid, int *i);
void	final_block(t_info *info);
int		execution_half(t_info *info, int *i);
void	handle_parent_cleanup(t_info *info, int *i);
void	child_cleanup_and_close(t_info *info);
int		is_heredoc(char **matrix);
int		*allocate_and_fill_heredocs(void);

// signals
void	estat(int i, t_info *info);
void	sstat(int i);
void	ctrl_c(int sig);
void	set_signals(void);

// intergration
void	save_redirections(t_info *info, t_token *token);
void	save_command(t_info *info, t_token **token);
void	save_other(t_info *info, t_token **token);
void	ft_conditions(t_info *info, t_token **token);
void	form_main(t_token *token, t_info *info);

// util functions
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	ft_refresh_fd(t_info *info);
int		if_out(char ***exec, int mat);
int		if_in(char ***exec, int mat);
void	ft_remove(char ***matrix);
int		is_val(const char *path, char *str);
char	*save_paath(char **envp);
void	fill_null(char ***tmp, int count);
int		first_setting(t_info *info, int ac,
			char **av, char **env);
void	init_loop(t_info *info);
void	last_setting(t_info *info);
void	act_block(t_token *token, t_info *info);
int		line_condition(char **line, t_token *token,
			t_info *info);
void	signal_reciever(t_info *info);
int		update_pwd(char ***matrix, t_info *info);
int		update_oldpwd(char ***matrix, t_info *info);

// free
void	free3(char ***matrix);
void	free_all(t_info *info);
void	padre(t_info *info);
void	free_heredocs(int **heredocs);

//parssing
/*quote_processing.c*/
char	*extract_single_quote_content(char *input, int *i);
char	*extract_double_quote_content(char *input, int *i, t_info *info);
t_token	*process_single_quote(t_parse_ctx *ctx);
t_token	*process_double_quote(t_parse_ctx *ctx);
char	*handle_quote_end(char *input, int *i,
			int content_start, char *full_segment);

/*syntax.c*/
int		validate_syntax(t_token *tokens, t_info *info, t_token *prev);
char	*token_type_to_string(t_token_type token_type);
t_token	*handle_special_chars(char *input, int *i, t_token *head,
			t_parse_ctx *full_ctx);
t_token	*handle_pipe(int *i, t_token *head, t_token *current);
t_token	*handle_redirection(char *input, int *i,
			t_token *head, t_token *current);
t_token	*handle_redirection_append(char *input, int *i);
t_token	*process_pipe(t_parse_ctx *ctx);

/*token_utils.c*/
t_token	*join_word_segment(char *segment, t_token *head,
			t_token **current_word_token, t_token_type type);
t_token	*add_new_token_to_list(char *segment, t_token *head,
			t_token **current_word_token, t_token_type type);
t_token	*append_to_existing_token(char *segment, t_token *head,
			t_token **current_word_token);
char	*join_and_free(char *s1, char *s2);
t_token	*process_redirection(t_parse_ctx *ctx);

/*tokenizer_core.c*/
t_token	*tokenize_input(char *input, t_info *info);
int		parse_tokens_loop(char *input, int *i, t_info *info, t_token **head);
int		handle_word_segment(char *input, int *i, t_token **head,
			t_token **current_word_token);
char	*extract_word_segment(char *input, int *i);

/*utils.c*/
t_token	*creat_token(char *content, t_token_type type);
t_token	*free_tokens(t_token *head);
t_token	*get_last_token(t_token *head);

/*variable_expansion.c*/
t_token	*handle_env_variable(char *input, int *i,
			t_token *head, t_parse_ctx *ctx);
char	*get_named_var_value(char *input, int *i, t_info *info);
char	*process_named_variable(char *input, int *i, t_info *info);
int		process_variable(char *input, int *i,
			t_info *info, char **full_segment);
int		append_text_segment(char *input, int *i,
			int content_start, char **full_segment);

#endif
