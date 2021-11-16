Unset
	- a ft_splitn(char *str, int n) would help to split string where we only want to split n times (useful for export)

Pipes
	- It seems that bash "locks" it's environment variable when a piped command line is being processed.
		- Example : (unset HEY | env) will not unset HEY and env will still show its value.
		- On zsh, only the last command can have lasting effect.
			- So, (unset HEY | env) will do nothing, but if unset is the last command, it will 	work.
	- Even ( cd example/dir | pwd ) will not change directory, and it also won't change the 	directory printed by (pwd)

cd / pwd
	- cd uses chdir(), which already handle "." and "..".
	- use getcwd() rather than parse

Terminal
	- find how to get the ctrl-D
	- find out how to get the ctrl-D

Export
	- Do error messages


___TESTS___

_Simple commands, compilation and globals_
- make -n
- CCFLAGS = -Wall -Wextra -Werror
- simple command with absolute path without options
/bin/ls
/bin/cat
- 1 global variables
- empty command line
- only spaces and/or tabs

_Arguments & history_
- simple command with absolute path with arguments without any quotes
	- try it multiple times

_echo_
echo hello world
echo "hello '' world"
echo -nnfds -n hello
echo "-n" hello
echo -n -n -n -a -n "-n hello"
echo "hello        world"
echo hello      world
echo hello "" world
echo -n
echo


_exit_
exit
exit [any_arguments]


_Return_
- execute any command with absolute path with arguments but without any quotes, then executes echo $?
- repeat in bash and compare value
- repeat with different commands and arguments, including failing commands
ls Idontexist
cat Idontexist
export 1= =
expr $? + $?
ls jg | echo $?

_Signals_
- ctrl-C : new line with new prompt with a clean buffer
- ctrl-\ should do nothing in an empty or non-empty prompt
- ctrl-D should quit minishell in an empty prompt
- ctrl-D should do nothing in a non-empty prompt
- ctrl-\ should do no