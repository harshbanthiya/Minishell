/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 08:37:55 by hbanthiy         ###   ########.fr       */
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
# include   "ms_tree.h"
# include   "ms_parse.h"
# include   "ms_execution.h"

#define ERROR -1
/* Global shell structure declaration */
struct s_shell	g_shell;

typedef struct s_cmd_str_node {
	char					*text;
	t_token_type			type;
}				t_cmd_str_node;

/* Return a formated prompt */
char	*ft_readline(void);
void	*ft_history(char *line);

/* Append (file) to (path), with a '/' in between */
char	*join_path_file(char *path, char *file);
/* Search for and return full path of specified "name" */
char	*get_path(char *name);

t_command   	*pipcmd2cmd(t_parse_node_pipcmds *pipcmds);
t_command   	*ast_cmd2cmd(t_parse_node_command *cmd_node);
char			*string_node2string(t_parse_node_string *string_node, bool add_quotes);
char			**expand_string_node(t_parse_node_string *string_node, bool is_export_cmd);
char			**split_expanded_str(char *str);
void			put_minish_err_msg(const char *cmd_name, const char *msg);
int				put_minish_err_msg_and_ret(int ret_val,
							const char *cmd_name, const char *msg);
void			put_minish_err_msg_and_exit(int status,
							const char *cmd_name, const char *msg);
void			check_malloc_has_success(char *cmd_name, void *ptr);
int				invoke_sequential_commands(t_parse_ast *seqcmd);
int				interactive_shell(void);

// Shell initialization
void					init_g_shell(void);
int						initialize_shell(void);


/* General Utils */
void			ft_err(char *pathname, char *argv_1);
void	    ctrl_d_exit(void);
char	    *append_char(char *org, char c);

/* Command Status */
int	        get_status(void);
void	    set_status(int status_value);
int	        set_status_and_ret(int status_value, int ret_value);
void	    show_parse_err(char *input_str);

#endif