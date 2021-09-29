#ifndef PARSE_H
#define PARSE_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

#define     MAX_VAR_NUM     10              /* Maximum number of Args: 10 */
#define     MAX_CMD_LEN     80              /* Maximum length of a command: 80 */
#define     MAX_PIPE_NUM    10              /* Maximum number of pipes: 10 */ 
#define     MAX_FILE_SIZE   40              /* File name size: 40 */
#define     TRUE            1
#define     FALSE           0
/* Parsing Information */
typedef struct      parse_info
{
    bool            background;
    char            *tokens[MAX_PIPE_NUM];
    int             numArgs;
    char            *inpipefile; /* File to be piped from */
    char            *outpipefile; /* File to be piped to */
}parse_info;

/* the function prototypes */
parse_info      *parse(char *);             
void            free_info(parse_info *);    
void            print_info(parse_info *);
void            init_info(parse_info *);
#endif 
