/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 21:42:09 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 13:44:13 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // TODO: stdio.h 헤더 삭제
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"

/*
** ==========================================================================
**  Global variables
** ==========================================================================
*/

int						*g_pipe_pid;
int						g_pipe_index;
int						g_pipe_test;
int						g_exit_code;
t_list					*g_curtok;

/*
** ==========================================================================
**  Constants
** ==========================================================================
*/

# define FALSE			0
# define TRUE			1
# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0
# define NO_EXCODE		-1
# define NO_STATUS		-1

# define SPACE			32
# define SEMICOLON		59
# define GREAT			62
# define GREATGREAT		2
# define LESS			60
# define PIPE			124
# define S_QUOTE		39
# define D_QUOTE		34
# define STRING			1
# define BACKSLASH		92

# define BUFF_SIZE		4096 // 버퍼 사이즈 적절한지 체크 필요

/*
** ==========================================================================
**  structs
** ==========================================================================
*/

typedef struct			s_token
{
	char	*data;
	int		type;
}						t_token;

typedef struct			s_scanner_flags
{
	int		s_quote;
	int		d_quote;
}						t_scanner_flags;

typedef struct			s_env
{
	char	*key;
	char	*val;
}						t_env;

typedef struct			s_rplc_env_note
{
	int		idx;
	int		end;
	int		crr;
}						t_rplc_env_note;

typedef struct			s_node
{
	int				type;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}						t_node;

typedef enum			e_nodetype
{
	NODE_PIPE = 100, // 0으로 설정시 비교되지 않음 (NULL POINTER와 동일)
	NODE_SEQ,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_OUT_DBL,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_DATA,
}						t_nodetype;

typedef struct			s_pipe
{
	bool	stdin_pipe;
	bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
}						t_pipe;

typedef struct			s_cmd
{
	int		argc;
	int		has_path;
	char	**argv;
	t_pipe	*pipe;
	t_node	*redir;
}						t_cmd;

/*
** ==========================================================================
**  command/
** ==========================================================================
*/

/*
** command/command_path.c
*/

char					**create_path_arr(t_list *env_path);
void					free_path_arr(char **path_arr);
void					free_tmp_env(char **env);
void					exec_with_path(t_cmd *cmd, char **path_arr, \
								t_list *env_list);

/*
** command/command_prepare.c
*/

void					command_count_argc(t_cmd *cmd, t_node *arg_node);
void					command_store_argv(t_cmd *cmd, t_node *arg_node, \
								t_list *env_list);
int						command_init(t_node *simple_cmd, t_cmd *internal, \
								t_pipe *pipe, t_list **env_list);
void					command_destroy(t_cmd *internal);

/*
** command/command.c
*/

void					command_internal_redir(t_cmd *cmd);
void					command_internal_pipe(int pid, t_cmd *cmd);
void					command_external_pipe(int pid, t_cmd *cmd);
void					command_external_redir(t_cmd *cmd);
void					command_execute(t_cmd *cmd, t_list **env_list);

/*
** ==========================================================================
**  envp/
** ==========================================================================
*/

/*
** envp/envp.c
*/

void					set_env_one(t_list **list, t_env *env);
void					print_env_list(t_list *env_head);
void					put_splitted_env(t_env **env, char *envp);
t_list					*set_env_list(char **envp);
char					**env_list_to_envp(t_list *env_head);

/*
** envp/sort_env.c
** envp/unset_env_one.c
*/

int						sort_env(t_list *env_list);
void					unset_env_one(t_list **env_head, char *key);

/*
** ==========================================================================
**  execute/
** ==========================================================================
*/

/*
** execute/exec_cd.c
** execute/exec_echo.c
** execute/exec_env.c
** execute/exec_exit.c
** execute/exec_export.c
** execute/exec_pwd.c
** execute/exec_unset.c
*/

int						exec_cd(t_cmd *cmd, t_list *env_list);
int						exec_echo(t_cmd *cmd);
int						exec_env(t_cmd *cmd, t_list **env_list);
int						exec_exit(t_cmd *cmd);
int						exec_export(t_cmd *cmd, t_list **env_list);
int						exec_pwd(t_cmd *cmd);
int						exec_unset(t_cmd *cmd, t_list **env_list);

/*
** execute/execute.c
*/
int						is_valid_env_key(char *env_key);
int						execute_internal_in_child(t_cmd *cmd, t_list **env_list);
int						execute_internal_in_parent(t_cmd *cmd, t_list **env_list);

/*
** ==========================================================================
**  interpret_tree/
** ==========================================================================
*/

/*
** interpret_tree/execute_pipe.c
*/

t_pipe					*pipe_first(int pipe_read, int pipe_write);
t_pipe					*pipe_mid(int pipe_read, int pipe_write);
t_pipe					*pipe_last(int pipe_read, int pipe_write);
t_pipe					*pipe_for_commamd(void);
t_pipe					*pipe_init(void);

/*
** interpret_tree/execute_tree.c
*/

void					execute_simplecmd(t_node *simple_cmd, t_pipe *pipe, \
								t_list **env_list);
void					execute_cmd(t_node *cmd_node, t_pipe *pipe, t_list \
								**env_list);
void					execute_pipeline(t_node *pipe_node, t_list **env_list);
void					execute_job(t_node *job, t_list **env_list);
void					execute_cmdline(t_node *cmdline, t_list **env_list);
void					execute_tree(t_node *head, t_list **env_list);
void					set_exit_code(int status, int excode);

/*
** ==========================================================================
** parse/
** ==========================================================================
*/

/*
** parse/node.c
*/

void					node_attach_branch(t_node *root, t_node *l_node, \
								t_node *r_node);
void					node_set_type(t_node *node, int type_num);
void					node_set_data(t_node *node, char *token);
void					node_delete(t_node	*node);
void					node_append_right(t_node **root, t_node *right);
void					node_count_pipe_node(t_node *search);
void					pre_order(t_node *search); // 추후 삭제

/*
** parse/parse_command.c
*/

t_node					*command(void);
t_node					*redir_list(void);
t_node					*simplecmd(void);

/*
** parse/parse_top.c
*/

t_node					*commandline(void);
t_node					*commandline_1(void);
t_node					*commandline_2(void);
t_node					*commandline_3(void);
t_node					*job(void);
t_node					*job_1(void);
t_node					*job_2(void);

/*
** parse/term.c
*/

int						term(int token_type, char **arg);
int						term_redir(char **arg, int *node_type);

/*
** ==========================================================================
**  scanner/
** ==========================================================================
*/

/*
** scanner/gen_token_string.c
** scanner/replace_env.c
** scanner/set_token_list.c
** scanner/strip_quotes.c
*/

int						gen_token_string(t_list **token_list, char *line, \
							int idx_start);
char					*replace_env(char *str, t_list *env_list);
int						set_token_list(t_list **token_list, char *line);
char					*strip_quotes(char **token_data);

/*
** scanner/util_replace_env1.c
*/

void					init_flag(t_scanner_flags **flag);
void					init_env(t_env **env);
void					init_replace_env(t_rplc_env_note **note, \
								char **result, t_env **env, \
								t_scanner_flags **flag);
int						is_valid_env_start(char chr1, char chr2, \
								t_scanner_flags *flag);
int						is_end_of_env_variable(char chr);

/*
** scanner/util_replace_env2.c
*/

void					set_quotes_status(char *line, int idx, t_scanner_flags \
								**flag);
int						set_env(t_env **env, char *str, int idx, \
								t_list *env_list);
void					free_env_flag_note(t_env *env, t_scanner_flags *flag, \
								t_rplc_env_note *note);

/*
** ==========================================================================
**  readline.c
** ==========================================================================
*/

char					*readline(void);
void					ctrl_d_exit(void);
char					*append_char(char *org, char c);

/*
** ==========================================================================
**  util.c
** ==========================================================================
*/

char					*replace_home_path(char *str, t_list *env_list);
void					print_err(char *pathname, char *argv_1);
void					free_env(void *env);
char					*get_env_val(char *key, t_list *env_list);
t_token					*create_token(char *line, int start, int end, int type);

#endif
