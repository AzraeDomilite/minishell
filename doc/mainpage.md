Minishell
=========

# test

see function main() and directory @ref libft/, also file shell.h.

# Todo

- merge new str functions to libft
- merge ptr_substr from printf folder to libft root folder
- why is enum not shown in doxygen doc?
- $? should expand to the return code of the last command. what happens with this value if there is a parse error? -> it is a value non equal to 0. what is the value when the shell is started? -> it is 0
- catch parse error, when cmd is empty or whole line is empty
- use a way to parse nested expressions, e.g. `(ls; echo "asdf") | cat`

# Open questions

## separator for commands

if you paste e.g. `ls ./a` and between ls and ./a is not a space but some other white space, will it work as a delimiter?

See man bash. Words are separated only by space and tab.

## variable setting

must minishell be able to set a variable like var1="content" ?

## variable expansion

is variable expansion only used in cmd and args or also in modifiers like < $file1? -> yes expansion must also work for modifiers

`asdf="ls"; $asdf`

## heredoc

what happens when a heredoc is pasted and it has the EOF on one line and there is content after? e.g.

```
<< STOP cat
asdf
bsdf
STOP123
```

# what happens in pipe if file out modifier specified

ls > csdf | cat

cat will not wait, what will it receive for STDIN? just an EOF?

man EOF: by closing the output pipe fd (e.g. STDIN of another program), the program is signaled that STDIN is closed.

## < << >> >

are variables allowed as file names?

## waiting for processes in a pipe

how to wait in the shell for all processes in a pipe?

STDIN and STDOUT can only be duplicated and therefore piped by a process itself. this means, that the end of the pipe must duplicated it's stdin and pass it to the next process in the pipe

the main shell process shall only continue if all processes in the pipe have finished. if the last process in the pipe does not wait for stdin, it will finish before the one before. how can the main process know, that all pipe processes have finished?

# Managing malloc and free

1. If an allocation is only needed temporary inside the function where it has been created, it will be freed in that same function
2. if an allocation is passed to a subfunction, but not needed anymore as soon as the subfunction will return, it will be freed in the parent function after the subfunction returned
3. If an allocation is passed outside of a function via return, it will be freed as soon as it is not needed anymore in the program
4. if an allocation will not be freed before the program ends, it will be freed with the end of the main function or an exit signal/handler of the program

# Resources

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
https://unix.stackexchange.com/questions/404054/how-is-a-process-group-id-set
https://stackoverflow.com/questions/2842809/lexers-vs-parsers
https://c-for-dummies.com/blog/?p=5195
https://unix.stackexchange.com/questions/302762/get-the-exit-code-of-processes-forked-from-the-master-process
https://unix.stackexchange.com/questions/278105/what-are-the-default-stdin-and-stdout-of-a-child-process
https://unix.stackexchange.com/questions/16883/what-is-the-maximum-value-of-the-process-id
https://stackoverflow.com/questions/9357464/how-to-start-a-shell-without-any-user-configuration