/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:19:53 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:09:46 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTION_H
# define MS_EXECUTION_H

# include <unistd.h>
# include "../libft/libft.h"
# include "ms_parse.h"

typedef struct s_cmd_redirection
{
    char                        *filepath;
    bool                        is_append;
    bool                        is_heredoc;
    int                         fd;
    struct s_cmd_redirection    *next;
}t_cmd_redirection;

/*
    A struct to remember all open fds to close them after finishing running commands 
*/

typedef struct s_fd_list
{
    int                 fd;
    struct s_fd_list    *next; 
}t_fd_list;

/*
    Keep input redirections or heredocs for each fd.
    "Heredoc_pipe" would be set to "pipe(heredoc_pipe)"
    if last element of 'reds' is heredoc
    You should get this struct through reds2in_fd_reds_list()
*/

typedef struct  s_fd_reds_list
{
    int                     fd;
    t_cmd_redirection       *reds;
    int                     heredoc_pipe[2];
    struct s_fd_reds_list   *next;
} t_fd_reds_list;

typedef struct  s_command
{
    t_cmd_redirection       *output_redirections;
    struct s_command        *piped_command;
    t_cmd_redirection       *input_redirections;
    char                    **exec_and_args;
    pid_t                   pid;
} t_command;

char					*find_executable_file_in_dir(
							char *filename, char *dirpath);
char					*find_executable_file_from_path_env(char *filename);
char					*find_executable_file_in_cwd(char *filename);
int						cmd_execvp(char *filename, char **argv);
int						cmd_exec_commands(t_command *command);
char					*expand_redirect_filepath(char *red_target);
int						open_file_for_redirect(t_cmd_redirection *red,
							int open_flags, mode_t open_mode);
int						put_redir_errmsg_and_ret(int ret_value,
							int fd, char *msg);
int						cmd_set_input_file(t_fd_reds_list *fd_red_list);
int						cmd_set_output_file(t_command *command);
void					cmd_exec_command(t_command *command,
							int pipe_prev_fd[2], int pipe_fd[2],
							t_fd_reds_list *in_fd_red_list);
int						cmd_exec_builtin(t_command *command);
void					cmd_close_pipe(int pipe_fd[2]);
void					cmd_copy_pipe(int pipe_new_fd[2], int pipe_fd[2]);
void					cmd_init_pipe_fd(int pipe_fd[2], int pipe0, int pipe1);
int						cmd_set_heredoc_pipe_fd(
							t_fd_reds_list *in_fd_red_list);
bool					cmd_is_heredoc_expandable(
							t_parse_node_redirection *redirection_node);
char					*expand_heredoc_document(char *str);
t_command               *cmd_init_cmd(char **exec_and_args);
t_command               *cmd_add_pipcmd(t_command **cmds, t_command *pipcmd);
int						cmd_add_inredirect(t_command *command,
							char *filepath, int fd);
int						cmd_add_heredoc(t_command *command,
							char *limit_str, int fd, bool is_expandable);
int						cmd_check_readline_has_finished(void);
void					cmd_set_heredoc_sighandlers(void);
int						cmd_add_outredirect(t_command *command,
							char *filepath, int fd, bool is_append);
void					cmd_free_cmd(t_command *cmds);
void					fd_list_close(t_fd_list **lst);
t_fd_list				*fd_list_add_fd(t_fd_list **lst, int fd);


#endif