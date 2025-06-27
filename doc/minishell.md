Minishell
=========

# interact with shell with python
https://unix.stackexchange.com/questions/25291/writing-to-stdout-except-for-output-redirection-c
https://stackoverflow.com/questions/9673730/interacting-with-bash-from-python
https://stackoverflow.com/questions/5068846/how-to-output-messages-to-stdout-on-another-thread-while-reading-from-stdin-with
https://stackoverflow.com/questions/15467164/why-does-readline-echo-stdin-to-stdout
https://stackoverflow.com/questions/55344848/how-to-direct-gnu-readline-away-from-stdout

# valgrind suppress

https://stackoverflow.com/questions/72840015/blocking-certain-functions-while-checking-leaks-with-valgrind

# Overview

A shell, when started, shows a prompt, that when RETURN is pressed, will be parsed and interpreted. Intrepreted means, depending on the text entered, an internal function (built-in) or external executable will be launched. Several functions/executables can be contained in the input, connected by pipes. After the actions referenced by the prompt have finished executing, the shell opens once again a prompt for the user.

The shell will quit when the builtin function exit is called or when it receives a kill signal by the shortcut CTRL+D.

A basic main function could look like this:

```
int main(void)
{
	while (not_exit_signal)
	{

	}
	return (0);
}
```

## Parsing the input

# Mandatory

First the single actions (built-in or executable) should be separated by splitting via redirections and pipes. A data type for storing the actions with their relations in regard to the pipes should be filled with the trimmed splits.

After that, the single actions can be parsed, beginning by splitting via spaces. Afterwards environment variables must be substituted and quotes parsed. What to do with unclosed quotes?

# Bonus

parsing of parentheses, logical operators and wildcards


# Parsing until a single command

- check if the initial command has brackets left or right. remove every bracket that has a pair left or right respectively
- go through the initial command string one char by char
- if a bracket, single or double quote opens, set a flag to true. reset it to false when the respective bracket or quote closes
- check the string for the operators in the order of precedence (if an operator is not found, start from the beginning of the string to check for another operator): ; -> &&/|| -> |
- how to handle <, >, << and >> ?
- if an operator is found, split the string here, set the operator of the current binary node to it and create to new nodes with the strings left and write of the operator
- call the parse function recursevly on those strings


# debug the binary tree

write a command that will traverse the binary tree and print it out by having a list and starting at the front node. recursively parse the nodes and make new lists, that will be inserted before the line of the current node (left node) or after the line of the current node (right node) you will having something like:

     [sed 's/from/to/g']
   __|
  /
[|]
  \
   ‾‾|
	  [echo "we're coming from Lausanne"]

	  
# execute the binary tree and parse the single command

 - now that you have a binary tree with separated commands, you can start to interpret the binary tree from the bottom left and parsing the commands one by one by combining them with the respective operators (the command on the left has to be executed first and then the command chain on the right)
-  how to pass stdin and stdout between those?
-  

# examples

## new lines in commands
```
cat << EOF
asdf
qwer
```

-> everything after newline will be interpreted as part of EOF, so detect the first newline in a command! (you actually have to copy paste it, to not activat the heredoc before)

```
cat
ls
ls
```

without here doc, everything will be interpreted

```
cat << EOF
asdf
qwer
EOFA
```

input will not end, because heredoc must end with a line "EOF", not "EOFA"

```
cat << EOF
asdf
qwer
EOF
ls
```

after cat with heredoc, the ls command will be executed

## other

```
cat << EOF << EOF
```

multiple here docs on one line


```
cat << EOF | cat
```

here docs can be anywhere, not just at the start

```
<< EOF cat
```

here docs have to be parsed first

## file pipes

`echo "asdf" > bsdf > csdf > cat`

will output asdf and write asdf to files bsdf and csdf

`echo "asdf" > asdf bsdf | cat`

writes asdf bsdf to file asdf bsdf and cats asdf bsdf

`echo "asdf " | < asdf cat`

echos asdf and discards the pipe, cat stdin will be filled only from file asdf

`echo "asdf" > < asdf bsdf | cat`

zsh: parse error near `<'

`cat bsdf < asdf | < bsdf cat`

< asdf in the middle will be ignored

`echo "hihi" | < asdf cat bsdf | < bsdf cat`

...

`< asdf csdf >`

zsh: parse error near `<'

`echo "hi" > csdf bsdf` works, but `< asdf > csdf bsdf`: zsh: command not found: bsdfq

`< asdf <bsdf cat >bsdf` bsdf will be nothing, if entry is empty

`baschnit@Gram:~/test$ < asdf (<bsdf | cat >bsdf)`
-bash: syntax error near unexpected token `('

# deleting with cat

`rm asdf | cat  asdf`

cat will output asdf and then asdf will be removed

`cat asdf | rm asdf`

asdf will be removed, and only then cat tries to output asdf which does not exist

# killing in a concatenation

`cat ;asdf`
 
 CTRL + C -> not only cat will be killed, but also asdf will never be executed

 # strange behaviour with open quote

 echo "asdf

 -> enter CTRL + D

 bash: unexpected EOF while looking for matching `"'
 but bash will continue to ask for lines

 enter " and it will ask again

# bash and zsh are behaving very differently!!!

- bash does not continue after first line if wrong opend or closed round bracket
- `< asdf > gedf cat < bsdf < csdf > dsdf > esdf >fedf`:
  - all files before fedf will be overwritten as empty
  - all input before csdf will be ignored
- `< asdf > gedf cat < bsdf < csdf > dsdf > esdf >fedf >> gedf`
  - all before gedf will be ignored
- `< asdf > gedf cat << EOF < bsdf < csdf << EOF > dsdf > esdf >> gedf > fedf`
  - user will be asked to times for heredoc, everything before the last here doc will be ignored
  - gedf will also be erased! only fedf will stay

```
baschnit@Gram:~/test$ < asdf cat > dsdf | cat
baschnit@Gram:~/test$ cat dsdf
asdf
baschnit@Gram:~/test$ < asdf cat | cat
asdf
baschnit@Gram:~/test$ < asdf cat | < bsdf cat
bsdf
baschnit@Gram:~/test$ 
```

a file output before or a file input after a pipe will break the pipe to the next program

`< asdf > usdf` only file pipes without a command will do nothing

# readline behaviour

readline takes newlines on pasting inside -> buffer all lines and execute command


# parsing

now trees are needed, if you call parse_separators recursively

#maybe change order of 0., 1. and 2. by splitting newlines into a buffer and taking from the buffer until buffer empty and only then do new readline if needed?

0. take readline and check if there is open single quote, double quote or round bracket. continue to read lines until everything is closed. if ) too much: parse error
1. no open quotes? check if last char is backslash, if yes, concatenate with next line, restart at 0
2. quote_split by separators
3. recursively run parse_separators on remaining parts
4. if there is no separator left, parse_pipes (which will give return value of command as int)
5. go back to parse_separators, to see how to continue with second part of split


## 0th function parse_line

## first function parse_control

## second function parse_pipe

https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators
https://stackoverflow.com/questions/2188199/how-to-use-double-or-single-brackets-parentheses-curly-braces


https://stackoverflow.com/questions/4589033/does-the-pointer-passed-to-free-have-to-point-to-beginning-of-the-memory-block


# test

test what happens if command starts with a closing bracket )

what for command like `ls && `, where nothing is following after && or `cat asdf |` where nothing is following after a pipe