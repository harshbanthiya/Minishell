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
