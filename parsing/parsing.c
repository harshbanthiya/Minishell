/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:45:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/30 15:19:52 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parsing.h"

int		is_delimiter(char c)
{
	if (c == '\0' || c == 34 || c == 39 || c == ' ')
		return (1);
	return (0);
}

// Takes the str address following the $ and return the environment variable value (or NULL)
t_var	*get_env_var(char *start)
{
	
	t_var	*var;
	int		i;
	int 	count;

	count = 0;
	if (start == NULL || !*start)
		return (NULL);
	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	while (!is_delimiter(start[count]))
		count++;
	var->name = (char *)malloc(sizeof(char) * (count + 1));
	if (var->name == NULL)
		return (var);
	i = -1;
	while (++i < count)
		var->name[i] = start[i];
	var->name[i] = '\0';
	var->value = getenv(var->name);
	return (var); 
}

// return 0 if not enclosed
int		is_enclosed(char *str, char c)
{
	while (str && *str)
	{
		if (*(str++) == c)
			return (1);
	}
	return (0);
}

// int		count_c(char *str, char delim)
// {
// 	int	count;

// 	count = 0;
// 	if (str == NULL)
// 		return (0);
// 	while (*str && *str != delim)
// 	{
// 		if (*str == '\"' && is_enclosed(str + 1, '\"'))
// 		{
// 			while (*(++str) != '\"')
// 				count++;
// 			count++;
// 		}
// 		str++;
// 		count++;
// 	}
// 	return (count);
// }

int	get_tok_end(char *str, char delim, int i)
{
	int		spc_flag;
	char	quote;

	spc_flag = 1;
	quote = '\0';
	if (str == NULL)
		return (i);
	while (str[i] && (str[i] != delim || !spc_flag))
	{
		if (str[i] == quote && !spc_flag)
		{
			spc_flag = 1;
			quote = '\0';
		}
		else if ((str[i] == '\'' && is_enclosed(str + 1, '\'')) || (str[i] == '\"' && is_enclosed(str + 1, '\"')))
		{
			spc_flag = 0;
			quote = str[i];
		}
		i++;
	}
	return (i);
}

//to continue
char	*expand_tok(char *tok)
{
	char	*exp_tok;
	t_var	*env_var;
	int		i;
	int		j;
	int		var_flag;

	i = 0;
	j = 0;
	var_flag = 1;
	exp_tok = NULL;
	env_var = NULL;
	while (tok[i])
	{
		j = i;
		while(tok[j] && !(tok[j] == '$' && var_flag))
		{
			if (tok[j] == '\'' && is_enclosed(&tok[j + 1], '\''))
				var_flag = 0;
			else if (tok[j] == '\'' && !var_flag)
				var_flag = 1;
			j++;
		}
		exp_tok = ft_str_append(exp_tok, &tok[i], j - i);
		if (tok[j] == '$')
		{
			env_var = get_env_var(&tok[j + 1]);
			if (env_var != NULL)
			{
			 	exp_tok = ft_str_fuse(exp_tok, env_var->value);
				 j += ft_str_len(env_var->name);
			}
		}
		i = j + 1;
	}
	exp_tok = ft_str_clean(exp_tok, "\'");
	exp_tok = ft_str_clean(exp_tok, "\"");

	
	return (exp_tok);
}

char	*tokenize(char *str, char delim, int *i)
{
	char	*tok;
	int		i_end;
	int		size;
	int		j;

	i_end = get_tok_end(str, delim, *i);
	size = i_end - *i;
	if (size == 0)
		return (NULL);
	tok = (char *)malloc(sizeof(char) * (size + 1));
	j = 0;
	while (*i != i_end)
	{
		tok[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	tok[j] = '\0';
	*i = i_end;
	return (tok);
}

t_tok *parse_input(char *str, char delim)
{
	t_tok	*tokens;
	char	*tok;
	int		i;

	tokens = NULL;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != delim)
		{
			tok = tokenize(str, delim, &i);
			if (tok == NULL)
				return (ft_free_tokens(tokens));
			tok = expand_tok(tok);
			ft_add_back(&tokens, ft_new_tok(tok));
		}
		else
			i++;
	}
	return (tokens);	
}

int	main(int argn, char **argv, char **envp)
{
	int		flag_exit = 0;
	char	*user_input;
	t_tok	*tokens;
	
	tokens = NULL;
	while (!flag_exit)
	{
		user_input = readline("prompt (\"quit\" to exit) : ");
		// user_input = get_env_var(user_input);
		if (user_input != NULL)
		 	add_history(user_input);
		tokens = parse_input(user_input, ' ');
		if (tokens == NULL)
			break;
		ft_print_tokens(tokens);
	}
	return (0);
}