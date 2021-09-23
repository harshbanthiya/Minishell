#include "struct.h"

/* 
    Lets launch jobs in response to commands typed by the user
    To create the processes in a process group, we can use fork and exec,
    But if multiple children are involved we must be careful to do them in the right order
    Or bad race conditions will crop up. 
 
    There are two choices on how to structure the tree of parent-child relationships among the processes
    1. We can either make all the processes in the process group be children of the shell process   
    2. Or we can make one process in group be the ancestor of all the other processes in the group. 
    The first approach is how shell does it and it is simpler to implement 
 
    As each process in forked, it should put itself in the new process group by calling setpgid()
    The first process in the new group is the process group leader, and its process ID becomes the process group ID for the group 
*/

/* 
    The shell must also call setpgid to put each of its child processes into the new process group. Because there might be a timing problem
    Each child process must be in the process group before it begins executing a new program. 

    If the job is being lauched in the foreground, the new process group must be put into foreground using tcsetpgrp() and should be done 
    for each of its child processes as well.

    The next thing a child needs to do is to reset its signal actions because during the initialisation it set shell to ignore all Signals
    As a result, child processes inherit the same ignorance of signals 
 
    Finally each child process should call exec in the normal way, this is also the point at which redirection of STDIN and STOUT needs 
    to be handled. 
 
    Here is the function to be executed by each child process immediately after being forked ();
*/

void    launch_process (process *p, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
    pid_t   pid;
    if (shell_is_interactive)
    {
        /* Put the process into the process group and give the process group the terminal, if appropriate
           This has to be done by the shell and in the individual child processes because of race conditions */
        pid = getpid();
        if (pgid == 0)
            pgid = pid;
        setpgid(pid, pgid);
        if (foreground)
            tcsetpgrp(shell_terminal, pgid);
        /* Set the handling for job control signals back to the default */
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);
    }
    if (infile != STDIN_FILENO)
    {
        dup2(infile, STDIN_FILENO);
        close(infile);
    }
    if (outfile != STDOUT_FILENO)
    {
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
    }
    if (errfile != STDERR_FILENO)
    {
        dup2(errfile, STDERR_FILENO);
        close(errfile);
    }
    /* Exec the new process and make sure we exit */
    exevp(p->argv[0], p->argv);
    perror("execvp\n");
    exit(1);
}

/* 
    if the shell is not running interactively, the above function does not do anything with process or signals 
    But a Shell not performing job control must keep all of its sub processes in the same process group as the shell itself
    Now a function that actually launches a complete job, after creating a child processes, the function calls some other functions 
    to put the newly created job into the forground or background. 
*/

void    launch_job(job *j, int foreground)
{
    process     *p;
    pid_t       pid;
    int         mypipe[2];
    int         infile;
    int         outfile;

    infile = j->stdin;
    p = j->first_process;
    while (p)
    {
        /* Setting up pipes where needed */
        if (p->next)
        {
            if (pipe(mypipe) < 0)
            {
                perror("pipe");
                exit(1);
            }
            outfile = mypipe[1];
        }
        else 
            outfile = j->stdout;
        
        /* Fork the child process */
        pid = fork();
        if (pid == 0)  /* This is the child process */
            launch_process(p, j->p_grp_id, infile, outfile, j->stderr, foreground);
        else if (pid < 0)
        {
            // fork failed 
            perror("fork");
            exit(1);
        }
        else 
        {
            // this is the parent process 
            p->pid = pid;
            if (shell_is_interactive)
            {
                if (!j->pgid)
                    j->pgid = pid;
                setpgid(pid, j->pgid);
            }
        }
        /* Clean up after pipes */
        if (infile != j->stdin)
            close(infile);
        if (outfile != j->stdout)
            close(outfile);
        infile = mypipe[0];
        p = p->next;
    }
    format_job_info(j, "launched");
    if (!shell_is_interactive)
        wait_for_job(j);
    else if (foreground)
        put_job_in_foreground(j, 0);
    else 
        put_job_in_background(j, 0);
}