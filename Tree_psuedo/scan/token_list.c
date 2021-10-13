#include "../shell.h"

token   *create_token(char *line, int start, int end, int type)
{
    token   *tok;

    tok = (token *)malloc(sizeof(token));
    if (!tok)
        return (0);
    tok->data = ft_strndup(&line[start], (end - start)); /* remember to write an str-N-dup function */
    tok->type = type;
    return (tok);
}

int     generate_special_token(list **token_list, char *line, int start_index)
{
    int     index;
    int     type;
    token   *tk;

    index = start_index;
    type = line[start_index];
    if (line[start_index] == '>' && line[start_index + 1] == line[start_index])
    {
        index++;
        type = ">>"; /* NOT single char make a flag later instead */
    }
    tk = create_token(line, start_index, index + 1, type);
    ft_lstadd_back(token_list, ft_lstnew(tk));
    return (index);
}

int     generate_string_token(list  **token_list, char *line, int start_index)
{
    int         index;
    token       *tok;
    scan_quote  *flag;
    char        *token_data;

    init_flag(&flag);
    index = start_index;
    while (line[index])
    {
        make_quote_status(line, index, &flag);
        if (is_end_str(line[index], flag))
            break ;
        index++;
    }
    free(flag);
    token_data = strndup(&line[start_index], index - start_index);
    tok = create_token(token_data, 0, ft_strlen(token_data), STRING);
    free(token_data);
    ft_lstadd_back(token_list, ft_lstnew(tok));
    if (line[index] != ' ')
        index--;
    return (index);
}    

int     make_token_list(list **token_list, char *line)
{
    int     index;
    int     line_len;

    line_len = ft_strlen(line);
    index = 0;
    while (index < line_len)
    {
        if (ft_strchr("<>|;", line[index]))
            index = generate_special_token(token_list, line, index);
        else if (line[index] == " ")
        {
            index++;
            continue ;
        }
        else 
            index = generate_string_token(token_list, line, index);
        if (index < 0)
            return (-1);
        index++;   
    }
}