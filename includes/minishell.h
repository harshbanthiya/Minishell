/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/24 18:39:59 by sfournie         ###   ########.fr       */
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
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<libft.h>

/* Contain the name and value of custom variables (shell, environment, etc.). */
typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

/* Node for generic chained list */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct termios	t_term;

/* Contain every pertinent informations worth being accessible globally */
typedef struct s_shell
{
    t_list	*env;		/* Chained list for environment/shell variables */
	t_term	def_term;	/* Default terminal (to be restored at the end!) */
	t_term	saved_term;	/* Used to save a terminal state to be restored later */
	int		sh_mode;	/* mode 1 : interactive, mode 0 : non-interactive */
	char	**builtins;	/* Contains the names of all our builtins */
	char	*pwd;
	int		fd[3];			/* 0 = input, 1 = output, 2 = error */
}				t_shell;

/* Global shell structure declaration */
struct s_shell	g_shell;

/* Shell */
void	init_shell(char **envp);	/* Master init function. Makes all the init calls needed. */
t_shell	*get_shell(void);
void	init_fd(int *fd);	/* set input, output and error fd */
void	sh_change_mode(int mode);
int		get_sh_mode(void);
/* End shell */

/* Reading */
char	*get_prompt(void);	/* Return a formated prompt */
char	*ft_readline(void);		/* Call readline() and w/e we want */
void	*ft_history(char *line);	/* Handle the history. Receive an input line.  */
/* End reading */

/* Parsing */
t_list	*tokenize(char *str, char delim);	/* Return a chained list of tokens based on parsing rules */
char	*expand_var(char *key);	/* Return the value of "name" if present in the variables list */
char	*clean_tok(char *tok);	/* "clean" the token received (remove or change characters) */
char	*parse_cmdline(char *line);
int		parse_is_delimiter(char c);
int		parse_is_escaped(char *str, int i);
int		parse_is_quotes(char *line, int i);
int		parse_is_enclosed(char *str, int i, char c);
int		parse_next_delim(char *str);
int		parse_is_var(char *line, int i);
int		parse_next_var(char *line, int i);
char	*parse_cleanup(char *line);
char	*parse_expand_line(char *line);
char	*parse_cmdline(char *line);
/* End parsing */

/* Execution */

/* End execution */

/* Environment	*/
t_list	*init_env(char **envp);		/* Fill the environment list with (envp) */
t_list	**get_env(void);			/* Return the environment list */
void	ft_env_export(int fd);
t_var	*get_var(char *key, t_list *list);
char	*get_var_value(char *key, t_list *list);
t_var	*new_var(char *key, char *value);
void	*dup_var(void *ptr);
void	print_var(int fd, t_var *var);
void	print_var_extra(int fd, t_var *var);	/* for export with no options */
char	*get_pwd();
void	set_pwd(char *pwd);
/* End environment */

/* Terminal */
void	init_terms(t_shell *sh, int term_fd);
void	term_save_state(int	term_fd);
void	term_restore_default();
void	term_restore_saved();
int		get_active_fd(void);
/* End terminal */

/* Signals */
void	init_signals(void);
void	sig_intr(int sig_num);
void	sig_eof(int sig_num);
void	sig_quit(int sig_num);
/* End signal */

/* Builtin commands */
char	**init_builtins();		/* Return a double array of all builtins' names */
int		is_builtin(char *name);		/* Return 1 if "name" is a builtin command */
int		run_builtin(char *cmd, char **args);	/* Return our exit code if any */
char	**get_builtins();	/* Return the global array of our builtin fcts */
int		ft_echo(char **tokens, int fd);	/* Return amount written. */
int		ft_cd(char **args);			/* Change working directory (variable and chdir()) */
void	ft_env(int fd);				/* Print a list of all shell variables */
void	ft_export(char **tokens, t_list **lst);		/* Parse and add/modify specified variable. */
void	ft_export_var(char *key, char *value, t_list **lst);
int		ft_unset(char **tokens, t_list **lst);	/* Parse and remove specified variable, if it exists */
int		ft_unset_var(char *key, t_list **lst);
int		ft_pwd(int fd);	/* Print current working directory */
int		ft_exit(void);	/* free everything and reset terminal to default */
/* End builtin commands */

/* Files/Directories */
char	*join_path_file(char *path, char *file);
char	*get_path(char *name);	/* Search for and return full path of specified "name" */
int		get_fd(int std);	/* std : 0 is stdin, 1 is stdout, 2 is stderr */
void	set_fd(int std, int fd);	/* std : 0 is stdin, 1 is stdout, 2 is stderr */
/* End Files/Directories */

/* Utilities */
/*		return a string with the content of each split[n] separated by (delim) */
char	*merge_split(char **split, char *delim);
char	**splitn(char const *s, char c, int n);
char	*ft_strfuse(char *str1, char *str2);
/* End utilities */

/* List */
t_list	*lst_new_node(void *content);
void	lst_add_front(t_list **lst, t_list *node);
void	lst_add_back(t_list **lst, t_list *node);
void	lst_remove_node(t_list *node, void *(del)(void *));
t_list	*lst_unlink_node(t_list **lst, t_list *node);	/* Unlink a node from a list and return it */
void	*lst_clear(t_list *lst, void *(del)(void *));
t_list	*lst_dup(t_list *lst, void *(iter)(void *), void *(del)(void *));
/* End list */

/* Memory */
/* They are prototyped to return a void *, but we don't have to work this way. */
void	*free_tokens(void *ptr);
void	*free_var(void *ptr);
void	*free_env(void *ptr);
void	free_shell(void);
void	*ft_free(void *ptr);	/* Generic free that will free() and return NULL */
void	*free_split(char **s);	/* Generic split free that will free() and return NULL */
/* End memory */

# endif