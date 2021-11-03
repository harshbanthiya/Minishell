#include "minishell.h"

void    init_flag(t_scan_quotes **flag)
{
    (*flag) = (t_scan_quotes *)malloc(sizeof(t_scan_quotes));
    if(!(*flag))
        return ;
    (*flag)->s_quote = 0;
    (*flag)->d_quote = 0;
}

/* It checks for single or double quotes that do not exist in pairs, and updates the struct flag when is finds non paired quotes */
void    make_quote_status(char *line, int index, t_scan_quotes **flag)
{
    if (line[index] == 34)
    { 
        if ((*flag)->s_quote == false && (*flag)->d_quote == false)
            (*flag)->d_quote = !((*flag)->d_quote); 
        else if ((*flag)->d_quote == true)
            (*flag)->d_quote = !((*flag)->d_quote);
    }
    if ((*flag)->d_quote == false && line[index] == 39) 
        (*flag)->s_quote = !(*flag)->s_quote;
}

int     is_end_str(char chr, t_scan_quotes *flag)
{
    if (flag->s_quote != true && flag->d_quote != true && ft_strchr(" |;<>", chr) != NULL)
        return (true);
    return (false);
}