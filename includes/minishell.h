/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/05 16:45:00 by sfournie         ###   ########.fr       */
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

/* Contain the name and value of custom variables (shell, environment, etc.). */
typedef struct s_var
{
	char	*name;
	char	*value;
}				t_var;

/* Node for generic chained list */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

/* Contain every pertinent informations worth being accessible globally */
typedef struct s_shell
{
    t_list	*env;		/* Chained list for environment/shell variables */
	struct termios	*def_term;	/* Default terminal (to be restored at the end!) */
	struct termios	*saved_term;	/* Used to save a terminal state to be restored later */
	struct termios	*active_term;	/* Current terminal (might not be needed) */
	int		stdin;
	int		stdout;
	int		stderr;
}				t_shell;

/* Global shell structure declaration */
struct s_shell	g_shell;

/*	Initialization */
void	ft_init_shell(char **envp);		/* Master init function. Makes all the init calls needed. */
void	ft_init_term();
t_list	*ft_init_env(char **envp);
/*	End initialization */

/*	Reading env */
char	*ft_get_prompt(void);	/* Return a formated prompt */
char	*ft_readline(void);		/* Call readline() and w/e we want */
void	*ft_history(char *line);	/* Handle the history. Receive an input line.  */
/*	End reading */

/*	Parsing */
t_list	*ft_tokenize(char *str, char delim);	/* Return a chained list of tokens based on parsing rules */
char	*ft_expand_var(char *name);	/* Return the value of "name" if present in the variables list */
char	*ft_clean_tok(char *tok);	/* "clean" the token received (remove or change characters) */
/*	End parsing */

/*	Execution */
/*	End execution */

/*	Terminal */
/*	End terminal */

/*	Builtin commands */
int		ft_is_builtin(char *name);	/* Return 1 if "name" is a builtin command */
int		ft_echo(char *str, int fd);	/* Return amount written. */
int		ft_cd(char *path);			/* Change working directory (variable and chdir()) */
void	ft_env(int fd);				/* Print a list of all shell variables */
int		ft_export(char *str, t_list **lst);		/* Parse and add/modify specified variable. */
int		ft_unset(char *name, t_list **lst);	/* Parse and remove specified variable, if it exists */
void	ft_pwd(void);				/* Print current working directory */
void	ft_exit(void);
/*	End builtin commands */

/*	"Get" functions */
t_shell	*ft_get_shell(void);
char	*ft_get_path(char *name);	/* Search for and return full path of specified "name" */
t_list	**ft_get_env(void);			/* Return the environment list */
/*	End "Get" */

/*	Utilities */
t_var	*ft_new_var(char *name, char *value);
/*	End utilities */

/*	List */
t_list	*ft_new_node(void *content);
void	ft_add_front(t_list **lst, t_list *node);
void	ft_add_back(t_list **lst, t_list *node);
void	ft_remove_node(t_list *node, void *(del)(void *));
void	ft_clear_list(t_list *lst, void *(del)(void *));
/*	End list */

/*	Memory */
/*	They are prototyped to work with void*, but we don't have to work this way. */
void	*ft_free_tokens(void *ptr);
void	*ft_free_var(void *ptr);
void	*ft_free_env(void *ptr);
void	*ft_free_shell(void *ptr);
void	*ft_free(void *ptr);	/* Generic free that will free() and return NULL */
void	*ft_free_split(char **s);	/* Generic split free that will free() and return NULL */
/* End memory */

int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char *s, char c);
void	ft_putstr_fd(char *s, int fd);

# endif