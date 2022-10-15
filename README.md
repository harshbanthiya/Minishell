  <h3 align="left">Minishell</h3>

  <p align="left">
    Short description
  </p>
  <p align="left">
    <a href="https://github.com/harshbanthiya/Minishell">
    <img src="https://badge42.vercel.app/api/v2/cl2xrmmu4000609mlo05k9qg8/project/2371023" alt="Minishell">
    </a>
 </p>
  
   ``Executable Name`` | ./minishell 
   :--------------- | :---------------
   ``Program Purpose`` | Making a small reimplementation of BASH with certain Limitations
   ``Program Language`` | C |
   ``Allowed External Library`` | readline 
   ``Allowed Functions & System Calls`` | printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit,getcwd, chdir, stat, lstat, fstat, unlink, execve,dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
   ``Tested Primarily on`` | MacOs    



## Table of contents

- [Usage](#Usage)
- [Built-in Functions by us](#Built-ins)
- [What's included](#whats-included)
- [Bugs and feature requests](#bugs-and-feature-requests)
- [Contributing](#contributing)
- [Creators](#creators)
- [Thanks](#thanks)
- [Copyright and license](#copyright-and-license)


## Usage

**To mimic Bash and it's usage for a single command**
```sh
bash -c "Command"
```
```sh
./minishell -c "Command"
```
**Or simply run the executable like bash**
```sh
bash
```
```sh
./minishell 
```
**To Exit**
```sh
ctrl + D
```


## Built-ins


Usually single quotes, double quotes and dollar sign are special characters that can cause expansion of variables.
Hence we needed to be thorough that our parsing is capable to handling a random mix of these special characters.
Following are the test cases of all the built-in functions we wrote.  

**Echo command**

```sh
./minishell
1: echo
2: echo echo
3: eCho
4: eChO
5: eCHO
6: ECHO
7: echo rhobebou
8: echo stop barking
9: echo "bonjour"
10: echo bonjour
11: echo 'bonjour'
12: echo -n bonjour
13: echo -nn bonjour
14: echo -n -n -n bonjour
15: echo -n -n -n bonjour
16: echo "-n" bonjour
17: echo -n"-n" bonjour
18: echo "-nnnn" bonjour
19: echo "-n -n -n"-n bonjour
20: echo "-n '-n'" bonjour
21: echo $USER
22: echo "$USER"
23: echo "'$USER'"
24: echo " '$USER' "
25: echo text"$USER"
26: echo text"'$USER'" ' $USER '
27: echo "text"   "$USER"    "$USER"
28: echo '              $USER          '
29: echo               text "$USER"            "$USER"text
30: echo ''''''''''$USER''''''''''
31: echo """"""""$USER""""""""
32: echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
33: echo $USER '' $USER $USER '' $USER '' $USER -n $USER
34: echo ' ' ' '
35: echo '" ' " """
36: echo " " " """ ''
37: echo "$USER""$USER""$USER"
38: echo text"$USER"test
39: echo '$USER' "$USER" "text ' text"
40: echo '$USER'
41: echo $USER " "
42: echo "$USER""Users/$USER/file""'$USER'"'$USER'
43: echo "$USER$USER$USER"
44: echo '$USER'"$USER"'$USER'
45: echo '"$USER"''$USER'"""$USER"
46: echo " $USER  "'$PWD'
47: echo " $USER  $ "'$PWD'
48: echo $USER=4
49: echo $USER=thallard
50: echo $USER
51: echo $?
52: echo $USER213
53: echo $USER$12USER$USER=4$USER12
54: echo $USER $123456789USER $USER123456789
55: echo $USER $9999USER $8888USER $7777USER
56: echo $USER $USER9999 $USER8888 $USER7777
57: echo $USER $USER9999 $USER8888 $USER7777 "$USER"
58: echo "$USER=12$USER"
59: echo "$9USER" "'$USER=12$SOMETHING'"
60: echo $PWD/file
61: echo "$PWD/file"
62: echo "text" "text$USER" ... "$USER"
63: echo $PWD
```

## What's included

Some text

```text
folder1/
└── folder2/
    ├── folder3/
    │   ├── file1
    │   └── file2
    └── folder4/
        ├── file3
        └── file4
```

## Bugs and feature requests

Have a bug or a feature request? Please first read the [issue guidelines](https://reponame/blob/master/CONTRIBUTING.md) and search for existing and closed issues. If your problem or idea is not addressed yet, [please open a new issue](https://reponame/issues/new).

## Contributing

Please read through our [contributing guidelines](https://reponame/blob/master/CONTRIBUTING.md). Included are directions for opening issues, coding standards, and notes on development.

Moreover, all HTML and CSS should conform to the [Code Guide](https://github.com/mdo/code-guide), maintained by [Main author](https://github.com/usernamemainauthor).

Editor preferences are available in the [editor config](https://reponame/blob/master/.editorconfig) for easy use in common text editors. Read more and download plugins at <https://editorconfig.org/>.

## Creators

**Creator 1**

- <https://github.com/usernamecreator1>

## Thanks

Some Text

## Copyright and license

Code and documentation copyright 2011-2018 the authors. Code released under the [MIT License](https://reponame/blob/master/LICENSE).

Enjoy :metal:
