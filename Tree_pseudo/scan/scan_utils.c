#include "../shell.h"

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
    if (line[index] == 34)  /* D quote use the enum later, it is breaking for now, 34 is the acii for double quote */
    {
        /* when I see the first double quote, I check if there is already any other quotes, if not, I make double quote equal to 1 */
        if ((*flag)->s_quote == false && (*flag)->d_quote == false)
            (*flag)->d_quote = !((*flag)->d_quote); /* when you ! (negate) an int, which is either positive or negative it becomes zero and zero becomes 1 */
        /* If not the above condition, then it means we have pair of d quotes, so I make it zero again */
        else if ((*flag)->d_quote == true)
            (*flag)->d_quote = !((*flag)->d_quote);
    }
    /* Similarly for single quotes */
    if ((*flag)->d_quote == false && line[index] == 39) /* 39 is the ascii val of single quote */
        (*flag)->s_quote = !(*flag)->s_quote;
}

int     is_end_str(char chr, t_scan_quotes *flag)
{
    if (flag->s_quote != true && flag->d_quote != true && ft_strchr(" |;<>", chr) != NULL)
        return (true);
    return (false);
}