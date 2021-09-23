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
    