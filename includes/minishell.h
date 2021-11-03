/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/02 15:36:20 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<sys/types.h>
# include	<termios.h>
# include	<signal.h>
# include	<sys/wait.h>
# include	<errno.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<stdbool.h>
# include	<fcntl.h>
# include	"libft.h"
# include	"dlist.h"
# include	"ms_builtin.h"
# include	"ms_environment.h"
# include	"ms_parsing.h"
# include	"ms_shell.h"
# include	"ms_signal.h"
# include	"ms_utility.h"

/* Globals and constants made for ease of testing remove later */
t_dlist  *global_current_token_node;
int     *global_pipe_pid;
int     global_pipe_index;
int     global_pipe_test;
int     global_exit_code;

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
# define LESSLESS   3
# define LESS			60
# define PIPE			124
# define S_QUOTE		39
# define D_QUOTE		34
# define STRING			1
# define BACKSLASH		92
# define BUFF_SIZE		4096

typedef struct s_token
{
	char	*data;
	int		type;
}						t_token;

typedef struct			s_scan_quotes
{
	int		s_quote;
	int		d_quote;
}						t_scan_quotes;

typedef struct			s_env
{
	char	*key;
	char	*val;
}						t_env;

typedef struct			s_rplc_env_node
{
	int		idx;
	int		end;
	int		crr;
}						t_rplc_env_node;

typedef struct			s_node
{
	int				      type;
	char			      *data;
	struct s_node	  *left_child;
	struct s_node	  *right_child;
}						t_node;

typedef enum e_nodetype
{
  NODE_PIPE = 100,
  NODE_REDIRECT_IN,
  NODE_REDIRECT_OUT,
  NODE_CMDPATH,
  NODE_ARGUMENT,
  NODE_REDIRECT_DOUBLEOUT,
  NODE_REDIRECT_DOUBLEIN,
  NODE_DATA,
  NODE_SEQ,
} t_node_type;

typedef struct  s_pipe
{
    bool    stdin_pipe;
    bool    stdout_pipe;
    int     read_pipe;
    int     write_pipe;
}t_pipe;

typedef struct  s_cmd
{
    int         argc;
    int         has_path;
    char        **argv;
    t_pipe      *pipe;
    t_node      *redir;
}t_cmd;

/* Global shell structure declaration */
struct s_shell	g_shell;

/* Return a formated prompt */
char	*ft_readline(void);
void	*ft_history(char *line);

/* Append (file) to (path), with a '/' in between */
char	*join_path_file(char *path, char *file);
/* Search for and return full path of specified "name" */
char	*get_path(char *name);

/* Function Calls */

/* Scan */
void    make_quote_status(char *line, int index, t_scan_quotes **flag);
int     is_end_str(char chr, t_scan_quotes *flag);
void    init_flag(t_scan_quotes **flag);
t_token   *create_token(char *line, int start, int end, int type);
int     generate_special_token(t_dlist **token_list, char *line, int start_index);
int     generate_string_token(t_dlist  **token_list, char *line, int start_index);
int     make_token_list(t_dlist **token_list, char *line);

/* Replace Env */
char    *replace_env(char *str, t_dlist *env_list);
char    *join_str_to_str(char *result, char *str, int start, int end);
int     gen_str_with_env(char **result, char *str, t_env *env, t_rplc_env_node *node);
void    free_env_flag_node(t_env *env, t_scan_quotes *flags, t_rplc_env_node *node);
int     set_env(t_env **env, char *str, int idx, t_dlist *env_list);
int     set_env_pos(char *str, int idx);
void    make_env_key_value(t_env **env, char *str, int len, t_dlist *env_list);
int     is_end_of_env_variable(char chr);
int     is_valid_env_start(char chr1, char chr2, t_scan_quotes *flags);
void    init_replace_env(t_rplc_env_node **node, char **result, t_env **env, t_scan_quotes **flags);

/* Parse */
int     term_redir(char **arg, int *node_type);
int     term(int token_type, char **arg);
t_node  *simplecmd(void);
t_node   *redir_list(void);
t_node   *command(void);
t_node   *job(void);
t_node   *job_2(void);
t_node   *job_1(void);
t_node   *cmd_line(void);
t_node	*cmd_line3(void);
t_node   *cmd_line2(void);
t_node   *cmd_line1(void);
void    node_set_data(t_node *node, char *token);
void    node_set_type(t_node *node, int type);
void    node_append_right(t_node **root, t_node *right);
void    node_attach_branch(t_node *root, t_node *left, t_node *right);
void	  node_delete(t_node *node);
void	  pre_order(t_node *search);
void	  set_exit_code(int status, int excode);

/* Interpret */
void    execute_tree(t_node  *head, t_dlist **env_list);
void    execute_job(t_node *job, t_dlist **env_list);
void    execute_pipeline(t_node *pipe_node, t_dlist **env_list);
void    execute_command(t_node *command, t_pipe *pipe, t_dlist **env_list);
void    execute_simplecmd(t_node *simple_cmd, t_pipe *pipe, t_dlist **env_list);
void    node_count_pipe_node(t_node *search);
t_pipe  *pipe_for_command(void);
t_pipe  *pipe_last(int read_pipe, int   write_pipe);
t_pipe  *pipe_mid(int read_pipe, int write_pipe);
t_pipe  *pipe_first(int read_pipe, int write_pipe);

/* Builtin */
int			execute_builtin_in_child(t_cmd *cmd, t_dlist **env_list);
int			execute_builtin_in_parent(t_cmd *cmd, t_dlist **env_list);
int			is_valid_env_key(char *env_key);

/* Env */
t_dlist    *make_env_list(char **envp);
void      update_kv_pair(t_env **env, char *envp);
void		print_env_list(t_dlist *env_head);
char		**env_list_to_envp(t_dlist *env_head);
void		set_env_one(t_dlist **list, t_env *env);
void		unset_env_one(t_dlist **env_head, char *key);

/* Cmd */
void    command_destroy(t_cmd *command);
int     command_init(t_node *simple_cmd, t_cmd *command, t_pipe *pipe, t_dlist **env_list);
void    command_store_argv(t_cmd *command, t_node *arg_node, t_dlist *env_list);
void    command_count_argc(t_cmd *command, t_node *arg_node);
void    command_execute(t_cmd *command, t_dlist ** env_list);
void    command_external_redir(t_cmd *command);
char    *strip_quotes(char **token_data);
void    exec_with_path(t_cmd *cmd, char **path_arr, t_dlist *env_list);
void    free_tmp_env(char **env);
void    free_path_arr(char **path_arr);
char    **create_path_arr(t_dlist *env_path);
char		*replace_home_path(char *str, t_dlist *env_list);
char		*get_env_val(char *key, t_dlist *env_list);
//char    *replace_env(char *str, t_dlist *env_list);

/* General Utils */
void			ft_err(char *pathname, char *argv_1);
void	    ctrl_d_exit(void);
char	    *append_char(char *org, char c);

#endif