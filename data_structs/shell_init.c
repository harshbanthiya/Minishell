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
            kill()

    }

}

