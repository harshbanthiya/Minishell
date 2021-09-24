#include "struct.h"

/* Initializing the shell */
/* When a shell program that normally performs job control is started, it has to be careful 
in case it has been invoked from another shell that is already doing its own job control.

A subshell that runs interactively has to ensure that it has been placed in the foreground by 
its parent shell before it can enable job control itself. It does this by getting its 
initial process group ID with the getpgrp function, and comparing it to the process group ID 
of the current foreground job associated with its controlling terminal (which can be retrieved 
using the tcgetpgrp function).

If the subshell is not running as a foreground job, it must stop 
itself by sending a SIGTTIN signal to its own process group. It may not arbitrarily put itself 
into the foreground; it must wait for the user to tell the parent shell to do this. If the subshell 
is continued again, it should repeat the check and stop itself again if it is still not in the foreground.

Once the subshell has been placed into the foreground by its parent shell, it can enable its own job control. 
It does this by calling setpgid to put itself into its own process group, and then calling tcsetpgrp to place 
this process group into the foreground.

When a shell enables job control, it should set itself to ignore all the job control stop signals so that it 
doesn’t accidentally stop itself. You can do this by setting the action for all the stop signals to SIG_IGN.

A subshell that runs non-interactively cannot and should not support job control. It must leave all processes 
it creates in the same process group as the shell itself; this allows the non-interactive shell and its child 
processes to be treated as a single job by the parent shell. This is easy to do—just don’t use any of the 
job control primitives—but you must remember to make the shell do it. */

pid_t               shell_pgid;
struct termios      shell_tmodes;
int                 shell_terminal;
int                 shell_is_interactive;


/* Make sure that shell is running interactively as the forground job before proceeding */

void    init_shell()
{
    /* see if shell is running interactively */
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty(shell_terminal); /* isatty(fd) determines if the fd is a valid terminal type device returns 1 and 0 */
    if (shell_is_interactive)
    {
        shell_pgid = getpgrp();
        while(tcgetpgrp(shell_terminal) != shell_pgid)
            kill(- shell_pgid, SIGTTIN); /* signals allow for manipulating processes, mostly terminating them. SIGTTIN - stop process 
                                            background read attempted from control terminal */
        
        /* Ignore interactive and job-control signals */
        signal (SIGINT, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
        signal (SIGTSTP, SIG_IGN);
        signal (SIGTTIN, SIG_IGN);
        signal (SIGTTOU, SIG_IGN);
        signal (SIGCHLD, SIG_IGN);

        /* Put ourselves in our own process group */
        shell_pgid = getpid();
        if (setpgid(shell_pgid, shell_pgid) < 0)  /* setpgid(pid_t pid, pid_t pgid) sets process pid's group to pgid returns zero on success */
        {
            perror("Couldn't put the shell in its own process group\n");
            exit(1);
        }

        /* Grab control of the terminal */
        tcsetpgrp(shell_terminal, shell_pgid); 
        /* tcsetpgrp(fd, pgid) if the process has a controlling terminal, this function sets the forground process group ID 
        associated with the terminal device to pgid, The terminal device associated with fd, must be controlling terminal of the
        calling process and the controlling terminal must be currently associated with the session of the calling process. The value of pgid
        must be the same as the process group ID of a process in the same session as the calling process */

        /* Save default terminal_attributes for shell */
        tcgetattr(shell_terminal, &shell_tmodes);
        /* tcgetattr(fd, termios_p) for getting the termios structure; 
         The tcgetattr() function copies the parameters associated with the terminal referenced by fildes in 
         the termios structure referenced by termios_p.
         This function is allowed from a background process; 
         however, the terminal attributes may be subsequently changed by a foreground process.*/
    }
}

