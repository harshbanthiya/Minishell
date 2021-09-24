#include "struct.h"

/* 
    When a foreground process is launched, the shell must block until all of the processes in that job have either terminated 
    or stopped. It can do this by calling waitpid function. We can use the WUNTRACED option so that status is reported for 
    processes that stop as well as processes that terminate

    The shell must also check on the status of background jobs so that it can report terminated and stopped jobs to the user;
    this can be done by calling waitpid with WNOHANG option. A good place to put a such a check for terminated and stopped jobs is
    just before prompting for a new command. 

    The shell can also receive asynchronous notification that there is status information available for a child process by
    establishing a handler for SIGCHLD signal.
    
    The SIGCHLD signal is normally ignored. This is to avoid reentrancy problems involving the global data structures the shell 
    manipulates. At specific times when the shell is not using these data structs - such as when waiting for input on the terminal
    it makes sense to enable a handler for SIGCHILD. The same function that is used to do the synchronous status checks can also
    be called from within this handler.
*/

/* Store the status of the process pid that was returned by waitpid. Return 0 if all went well, nonzero otherwise */

int     mark_process_status(pid_t pid, int status)
{
    job         *j;
    process     *p;

    if (pid > 0)
    {
        /* Update the record for the process */
        j = first_job;
        while (j)
        {
            p = j->first_process;
            while (p)
            {
                if (p->pid == pid)
                {
                    p->status = status;
                    if (WIFSTOPPED(status))
                        p->stopped = 1;
                    else 
                    {
                        p->completed = 1;
                        if (WIFSIGNALED(status))
                            fprintf(stderr, "%d: Terminated by signal %d.\n", 
                                (int)pid, WTERMSIG(p->status));
                    }
                    return (0);
                }
                p = p->next;
            }
            fprintf(stderr, "No child process %d.\n", pid);
            return (-1);
            j = j->next;
        }
    }
    else if (pid == 0 || errno == ECHILD
        return (-1); /* No processes ready to report */
    else 
    {
        /* Other weird errors */
        perror("Waitpid");
        return (-1);
    }
}

/* Check for processes that have status information available, without blocking */

void    update_status(void)
{
    int     status;
    pid_t   pid;

    pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
    while (1)
    {
        if (mark_process_status(pid, status))
            break ;
        pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
    }
}

/* Check for processes that have status information available, blocking 
    until all processes in the given job have reported */

void    wait_for_job(job *j)
{
    int     status;
    pid_t   pid;

    pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    while (1)
    {
        if(mark_process_status(pid, status) && job_is_stopped(j) && job_is_completed(j))
            break ;
        pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    } 
}

/* Format information about job status for the user to look at */

void    format_job_info(job *j, const char *status)
{
    fprintf(stderr, "%ld (%s): %s\n",(long)j->pgid, status, j->command);
}

/* Notify the user about stopped or terminated jobs. Delete terminated jobs from the active job list. */

void    do_job_notification(void)
{
    job     *j;
    job     *jlast;
    job     *jnext;

    /* Update status information for child process */
    update_status();
    jlast = NULL;
    j = first_job;
    while (j)
    {
        jnext = j->next;
        /* If all processes have completed, tell the user the job has completed and delete it from the list 
            of active jobs */
        if (job_is_completed(j))
        {
            format_job_info(j, "completed");
            if (jlast)
                jlast->next = jnext;
            else 
                first_job = jnext;
            free_job(j);
        }

        /* Notify the user about stopped jobs, marking them so that we won't do this more than once */
        else if (job_is_stopped(j) && !j->notified)
        {
            format_job_info(j, "stopped");
            j->notified = 1;
            jlast = j;
        }
        /* Dont say anything about jobs that are still running */
        else 
            jlast = j;
        j = jnext;
    }
}

/* 
    CONTINUING STOPPED PROCESSES 

    The shell can continue a stopped process using SIGCONT signal to the process group. 
    If the job is being continued in the foreground, the shell should invoke tcsetpgrp() to give the job access to 
    the terminal, and restore saved terminal settings. After continuing a job in the foreground, the shell should wait 
    for the job to stop or complete, as if the job had just been lauched in the foreground. 

    This shell program handles both newly created and continued jobs with the same pair of functions, put_job_in_foreground
    and put_job_in_background. When continuing a stopped job, a non zero value is passed as the cont argument to ensure that 
    SIGCONT signal is sent and the terminal modes are reset as appropriate 
*/


/* Mark a stopped job J as being running again */

void    mark_job_as_running(job *j)
{
    process *p;

    p = j->first_process;
    while (p)
    {
        p->stopeed = 0;
        p = p->next;
    }
    j->notified = 0;
}

/* Continue the job J */


void    continue_job(job *j, int foreground)
{
    mark_job_as_running(j);
    if (foreground)
        put_job_in_foreground(j, 1);
    else 
        put_job_in_background(j, 1);
}

