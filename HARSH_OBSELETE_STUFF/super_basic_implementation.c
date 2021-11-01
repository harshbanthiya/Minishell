#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define  TOKEN_BUFFSIZE 64
#define   TOKEN_DELIMITER_STR " \t\r\n\a"
unsigned char  *command_line_buffer = (char *) NULL;
int ft_cd(char **args);
int ft_echo(char **args);
int ft_exit(char **args);
char *builtin_str[] = {
  "cd",
  "echo",
  "exit"
};
int (*builtin_func[]) (char **) = {
  &ft_cd,
  &ft_echo,
  &ft_exit
};
int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
int ft_exit(char **args)
{
  return 0;
}

int ft_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
/* Read cl(Command line) reads a string, and returns a pointer to it, RETURNS NULL on EOF */
char   *read_cl(void)
{
    /* If the buffer has already  been allocated, return Memory to the pool */
    if (command_line_buffer)
    {
        free(command_line_buffer);
        command_line_buffer = (char *) NULL;
    }
    /* Get the line */
    command_line_buffer = readline("$ ");
    /* If the line has text save it to history */
    if (command_line_buffer && *command_line_buffer)
        add_history(command_line_buffer);
    return (command_line_buffer);
}

/* 
    split line tokenises the line using the space delimters but doesnt, do anything about escape
    characters 
*/
char        **split_line(char   *line)
{
    int     buffsize;
    int     position;
    char    **tokens;
    char    *token;

    buffsize = TOKEN_BUFFSIZE;
    position = 0;
    tokens = malloc(buffsize * sizeof(char *)); 
    if (!tokens)
    {
        perror("Error in allocating Token space\n");
        exit(1);
    }
    token = strtok(line, TOKEN_DELIMITER_STR);
    while (token != NULL)
    {
        tokens[position++] = token;
        if (position >= buffsize)
        {
            buffsize += TOKEN_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens)
            {
                perror("Error in allocating extra token space\n");
                exit(1);
            }
        }
        token = strtok(NULL, TOKEN_DELIMITER_STR);
    }
    tokens[position] = NULL;
    return (tokens);
}

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return ft_launch(args);
}
void loop (void)
{
    char        *line;
    char        **args;
    int         status; 


    /* Read commands entered by the user */
    /* Parse the commands  */
    /* Execute the commands */
    status = 1;
    while (status)
    {
        line = read_cl();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    }
}

/* 
    BUILT IN functions cd pwd echo exit 
    used as function pointers 
*/

int     ft_cd(char **args)
{
    if (strcmp("cd", args[0]) == 0)
    {
        /* to get pwd we can use the struct below, for more details on the struct man pwuid */
        struct passwd   *pwd;
        char            *path;

        path = args[1];
        if (path == NULL)
        {
            pwd = getpwuid(getiuid());
            path = pwd->pw_dir;
        }
        if (path[0] == '/')
            (path) = ++(path);
        errno = chdir(path);
        if (errno != 0)
            perror("Error changing directory\n");
    }
    return (1);
}

int     ft_echo(char **args)
{
    int     i;
    int     no_nl;
    i = 1;
    no_nl = 0;
    if (strcmp("echo", args[0]) == 0)
    {
        if (strcmp("-n", args[1]) == 0)
            no_nl = 1;
        while(args[i] != NULL)
        {
            printf("%s", args[i++]);
            
        }
        if (no_nl)
                return ;
        else 
            printf("\n");
    }
    return (1);
}
int main(int argc, char **argv)
{
    /* As soon as you start shell, you load the configuration files */


    /* Run a read evaluate print loop */
    loop();


    /* Shut down and clean up */

    return (0);
}   