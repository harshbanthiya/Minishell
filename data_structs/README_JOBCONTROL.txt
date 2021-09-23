Concepts of Job Control 

The fundamental purpose of interactive shell is 
    1 - to read commands from user terminal     
    2 - to create processes to execute the programs specified in those commands 
            (fork and exec)

A single command may run just one process but often one command uses several processes. 
If you use the '|' operator you request several programs in their own processes. But even if you run just the one program, it can use 
multiple processes internally. 

Like compilation uses 'cc -c foo.c' typically uses four processes. 

The processes belonging to a single command is called a "process group" or "job";
This is so that you can operate on all of them at once. 
cc -c sends signal SIGINT to terminate all processes in the foreground process group

A session is a larger group of processes. Normally all processes that stem from a single login belong to the same session.

Every process belongs to a process group,
    When a process is created, it becomes the member of the same process group and session as its parent process.
    We can put it in another process group using setpgid function, provided the process belongs to the same session
    The only way to put a process in a different session is to make it the initial process of a new session, using setsid function 

Important 

A shell that supports job control must arrange to control which job can use the terminal at the time. 
    Otherwise there might be multiple jobs trying to read from the terminal at once, and the confusion about which process should receive
    the input. To prevent the confusion, the shell must cooperate the terminal driver using the protocol described below 


The shell can give unlimited access to the controlling terminal to only one process group at a time. 
This is called a foreground job on that controlling terminal. Other process groups managed by the shell that are executing without the 
access to the terminal are called background jobs.


