#include "struct.h"

/* 
    Lets make the actions required by the shell to launch a job into the foreground and how this differs from what must be done
    in the background. 

    When a foreground job is launched the shell must first give it access to the controlling terminal by calling tcsetpgrp.
    Then the shell should wait for the processes in that process group to terminate or stop. 

    When all of the processes in the group have either completed or stopped, the shell should regain control of the terminal
    for its own process group by calling tcsetpgrp. Since stop signals caused by I/O from background process or SUSP character typed
    by the user are sent to the process group, normally all the processes in the job stop together

    The foreground may have left the terminal in a strange state, so the shell should restore its own saved terminal modes before
    continuing. In case the job is stopped, the shell should first save the current terminal modes so that it can restore tehm later 
    if teh job is continued. 
*/

/* 
    Put job J in the foreground. If cont is nonzero, restore saved terminal modes and send the process group a SIGCONT signal 
    to wake it up before we block.
*/

void    put_job_in_foreground(job *j, int cont)
{
    /* Put the job in the foreground */
    tcsetpgrp(shell_terminal, j->pgid);
    /* Send the job a continue signal, if necessary */
    if (cont)
    {
        tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
        if (kill (- j->pgid, SIGCONT) < 0)
            perror("kill(SIGCONT)");
    }
    /* Wait for it report back */
    wait_for_job(j);

    /* Put shell back in the foreground */
    tcsetpgrp(shell_terminal, shell_pgid);

    /* Restore the shell's terminal modes */
    tcgetattr(shell_terminal, &j->tmodes);
    tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

/* 
    If the process group is launched as the background job, the shell should remain in the foreground itself and continue to read
    commands from the terminal. 
*/

/* 
    Put a job in the background. If the cont argument is true, send the process group a SIGCONT signal to wake it up. 
*/

void    put_job_in_background(job *j, int cont)
{
    /* Send the job a continue signal, if necessary */
    if (cont)
    {
        if (kill(-j->pgid, SIGCONT) < 0)
            perror("kill (SIGNCONT)");
    }
}