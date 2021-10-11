/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/11 17:50:53 by sfournie         ###   ########.fr       */
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
	t_term	*def_term;	/* Default terminal (to be restored at the end!) */
	t_term	*saved_term;	/* Used to save a terminal state to be restored later */
	t_term	*active_term;	/* Current terminal (might not be needed) */
	char	**builtins;	/* Contains the names of all our builtins */
	int		fd[3];			/* 0 = input, 1 = output, 2 = error */
}				t_shell;

/* Global shell structure declaration */
struct s_shell	g_shell;

/* Shell */
void	init_shell(char **envp);		/* Master init function. Makes all the init calls needed. */
t_shell	*get_shell(void);
/* End shell */

/* End initialization */

/* Reading */
char	*get_prompt(void);	/* Return a formated prompt */
char	*ft_readline(void);		/* Call readline() and w/e we want */
void	*ft_history(char *line);	/* Handle the history. Receive an input line.  */
/* End reading */

/* Parsing */
t_list	*tokenize(char *str, char delim);	/* Return a chained list of tokens based on parsing rules */
char	*expand_var(char *key);	/* Return the value of "name" if present in the variables list */
char	*clean_tok(char *tok);	/* "clean" the token received (remove or change characters) */
/* End parsing */

/* Execution */

/* End execution */

/* Environment	*/
t_list	*init_env(char **envp);		/* Fill the environment list with (envp) */
t_list	**get_env(void);			/* Return the environment list */
void	ft_env_sorted(int fd);
t_var	*get_var(char *key, t_list *list);
t_var	*new_var(char *key, char *value);
void	print_var(int fd, t_var *var);
void	print_var_extra(int fd, t_var *var);	/* for export with no options */
/* End environment */


/* Terminal */
void	init_terms(t_shell *sh, int term_fd);
void	set_saved_term(t_term *term);
void	set_def_term(t_term *term);
void	set_active_term(t_term *term);
t_term	*get_saved_term(void);
t_term	*get_def_term(void);
t_term	*get_active_term(void);
/* End terminal */

/* Builtin commands */
char	**init_builtins();		/* Return a double array of all builtins' names */
int		is_builtin(char *name);		/* Return 1 if "name" is a builtin command */
int		run_builtin(char *name);	/* Return our exit code if any or pertinent */
char	**get_builtins();	/* Return the global array of our builtin fcts */
int		ft_echo(int fd, char *str);	/* Return amount written. */
int		ft_cd(char *path);			/* Change working directory (variable and chdir()) */
void	ft_env(int fd);				/* Print a list of all shell variables */
void	ft_export(char *str, t_list **lst);		/* Parse and add/modify specified variable. */
int		ft_unset(char *key, t_list **lst);	/* Parse and remove specified variable, if it exists */
int		ft_pwd(void);				/* Print current working directory */
int		ft_exit(void);
/* End builtin commands */

/* Files/Directories */
char	*get_path(char *name);	/* Search for and return full path of specified "name" */
/* End Files/Directories */

/* Utilities */

/* End utilities */

/* List */
t_list	*lst_new_node(void *content);
void	lst_add_front(t_list **lst, t_list *node);
void	lst_add_back(t_list **lst, t_list *node);
void	lst_remove_node(t_list *node, void *(del)(void *));
t_list	*lst_unlink_node(t_list **lst, t_list *node);	/* Unlink a node from a list and return it */
void	*lst_clear(t_list *lst, void *(del)(void *));
t_list	*env_lst_dup(t_list *lst, void *(del)(void *));
/* End list */

/* Memory */
/* They are prototyped to work with void *, but we don't have to work this way. */
void	*free_tokens(void *ptr);
void	*free_var(void *ptr);
void	*free_env(void *ptr);
void	free_shell(void);
void	*ft_free(void *ptr);	/* Generic free that will free() and return NULL */
void	*free_split(char **s);	/* Generic split free that will free() and return NULL */
/* End memory */

# endif