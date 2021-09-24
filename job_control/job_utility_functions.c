#include "struct.h"
/* Some utility functions to operate on the jobs object */

/* Find the active job with the indicated p_g_id */
job     *find_job(pid_t p_gid)
{
    job     *j;

    j = first_job;
    while(j)
    {
        if (j->p_grp_id == p_gid)
            return (j);
        j = j->next;
    }
    return (NULL);
}

/* Return True if all processes in the job have stopped or completed */
int     job_is_stopped(job *j)
{
    process     *p;

    p = j->first_process;
    while (p)
    {
        if (!p->completed && !p->stopped)
            return (0);
        p = p->next;
    }
    return (1);
}

/* Return True if all processes in the job have completed */
int     job_is_completed(job *j)
{
    process     *p;

    p = j->first_process;
    while (p)
    {
        if (!p->completed)
            return (0);
        p = p->next;
    }
    return (1);
}