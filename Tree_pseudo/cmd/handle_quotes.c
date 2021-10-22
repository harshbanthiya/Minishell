#include "../shell.h"
#define BUFFER_SIZE 4096

int	calc_buff_len(int *buff)
{
	int	idx;
	int	len;

	len = 0;
	idx = 0;
	while (idx < BUFFER_SIZE)
	{
		if (buff[idx] == 1)
			len++;
		idx++;
	}
	return (len);
}

char	*create_result_str(int *buff, char *token_data, scan_quote *flag)
{
	int		idx;
	int		cnt;
	char	*result;

	if (flag->d_quote == true || flag->s_quote == true)
	{
		write(1, "Wrong Token!\n", 13);
		result = ft_strdup("");
		return (result);
	}
	cnt = calc_buff_len(buff);
	result = ft_calloc(cnt + 1, sizeof(char));
	result[cnt] = '\0';
	idx = 0;
	cnt = 0;
	while (idx < BUFFER_SIZE && token_data[idx] != '\0')
	{
		if (buff[idx] == 1)
		{
			result[cnt] = token_data[idx];
			cnt++;
		}
		idx++;
	}
	return (result);
}

int     strip_quotes_other(char *token_data, int **buff, int index, scan_quote **flags)
{
    if (token_data[index] == 39)
        (*flags)->s_quote = false;
    if ((*flags)->s_quote == false && token_data[index] == 34)
        (*flags)->d_quote = !((*flags)->d_quote);
    if (token_data[index] != 39 && token_data[index] != 34)
        (*buff)[index] = 1;
    return (index + 1);
}

int     strip_quotes_single(char *token_data, int **buff, int index, scan_quote **flags)
{
    if ((*flags)->d_quote == true)
        (*buff)[index] = 1;
    else 
        (*flags)->s_quote = true;
    index++;
    while ((*flags)->d_quote == false && token_data[index] != '\0' && token_data[index] != 39)
    {
        (*buff)[index] = 1;
        index++;
    }
    return (index);
}

char    **strip_quotes(char **token_data)
{
    char            *result;
    scan_quote      *flags;
    int             index;
    int             buff[BUFFER_SIZE];
 
    init_flag(&flags);
    ft_bzero(buff, BUFFER_SIZE);
    index = 0;
    while ((*token_data)[index] != '\0')
    {
        if ((*token_data)[index] ==  39 && flags->s_quote == false)  /* 39 is ascii for single quote */
            index = strip_quotes_single(*token_data, &buff, index, flags);
        else 
            index = strip_quotes_other(*token_data, &buff, index, flags);
    }
    result = create_str_result(buff, *token_data, flags); /* Make this function */
    free((*token_data));
    free(flags);
    return (result);
}