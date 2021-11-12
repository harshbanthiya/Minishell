#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#define TMPFILE ".here_doc"
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_memdel(void **ap);
void	ft_strdel(char **as);

bool	is_limiter_line(char *limiter, char **line)
{
	if (ft_strncmp(*line, limiter, ft_strlen(limiter)))
	{
		ft_strdel(line);
        return (true);
	}
	return (true);
}

bool	write_to_tmp(int tmp_fd, char **line)
{
	int	i;
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '\\')
			i++;
		/*
		if ((*line)[i] == '$')
			handle_dollar()   // Make this function or maybe SEB has it, expand the value of a variable from env 
 		*/
		if (write(tmp_fd, &(*line)[i], 1) < 0)
		{
			ft_strdel(line);
			return (0);
		}
	}
	if (write(tmp_fd, "\n", 1) < 0)
	{
		ft_strdel(line);
		return (0);
	}
	ft_strdel(line);
	return (true);
}

bool	here_doc_as_token(char *limiter)
{
	char		*line;
	int			retval;
	int 		fd;
	
	fd = open(TMPFILE, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		printf("File creation error for heredoc\n");
	while (1)
	{
		line = readline("heredoc>");
		/* Changed some stuff go back to original implementation when stuck, SEB dont run this, it isnt functional yet */ 
		if (!is_limiter_line(limiter, &line))
			break ;
		if (line <= 0)
			break ;
        if (!write_to_tmp(fd, &line))
			return (0);
	}
	return (true);
}

int main(int argc, char **argv)
{
    char    *line;
    char    *prompt;
    int     i;
    i = 6;
    line = 0;
    prompt = "heredoc>";
    here_doc_as_token("EOF");
	/* while(--i)
    {
        line = readline(prompt);
        here_doc_as_token("EOF");
		if (line == NULL)
            break;
        printf("%s\n", line);
        free(line);
    }
	*/
    return (0);
}
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str++)
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (index);
	while (*s1 && *s2 && index < n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		index++;
	}
	if (index == n)
	{
		s1--;
		s2--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}
void	ft_strdel(char **as)
{
	ft_memdel((void **)as);
}