#ifndef STRUCTS_H
#define STRUCT_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>

/*  termios functions describe a general terminal interface that
    is provided to control asynchronous communications ports. */

// The job data type contains information about a job, which is a set of subprocesses linked together with pipes. 
// The sub data type is called a process which holds information about the subprocess. 


/* A process is a single process */
typedef struct process
{
    struct process      *next;          /* next process in the pipeline */
    char                **argv;         /* for execution */
    pid_t               pid;           /* process id */
    char                completed;     /* true if process is completed */
    char                stopped;       /* true if process is stopped */
    int                 status;        /* reported status value */ 
} process; 

/* A job is a pipeline of processes */
typedef struct  job
{
    struct job          *next;         /* next active job */
    char                *command;      /* command line, used for messages */
    process             *first_process; /* list of processes in this job */
    pid_t               p_grp_id;      /* process group id */
    char                notified;      /* true if user told about stopped job */
    struct terminos     tmodes;        /* saved terminal modes */
    int                 stdin;         /* standard I/O channels */
    int                 stdout;        /* standard I/O channels */
    int                 stderr;        /* standard I/O channels */
} job;

job     *first_job = NULL;

/* Function Calls */

job     *find_job(pid_t p_gid);
int     job_is_stopped(job *j);
int     job_is_completed(job *j);

#endif

