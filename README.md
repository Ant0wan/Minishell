# Minishell [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)
[![Build Status](https://travis-ci.com/Ant0wan/Minishell.svg?branch=master)](https://travis-ci.com/Ant0wan/Minishell)

An implementation of a very tiny **shellscript** [a 42 project].

This project aims to get familiar with some of the core of the Unix system and explore an important part of the system’s API: process creation and synchronisation.

## Description

Minishell is a mini UNIX command interpreter. Its prompt displays the current repository and wait a command line ending with the `return` key pressed from keyboard. The prompt is shown again only once the command has been completely executed.

The command lines are simple, no pipes, no redirections or any other advanced functions. However multiple commands can be entered using the `;` character to separate commands. If `builtin` keyword or if the command line is not a minishell builtin, the input is executed with the binaries found with PATH environment variable.

In cases the binary cannot be found, minishell returns an error message and display its prompt again.

Errno was forbidden by the project. Therefore, a specific module `Error` has been coded.

Environment variables are retreived using `char **environ` given by `unistd.h`.

Minishell has the following builtins: `exit` (POSIX compliant), `echo` (POSIX compliant), `cd` (POSIX compliant), `env` (POSIX compliant), `pwd` (POSIX compliant), `setenv` (tcsh version) and `unsetenv` (tcsh version).
    
Bash was the shell reference during the project, thereby minishell behavior refers to bash one.

The following expansions are supported and substituted at lexing time: `$`, `$?`, `${}`, `~`, `~+` and `~-`.

Minishell has been coded refering to the POSIX standard (IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)), however it does not fully comply to the standard.

Minishell uses the following functions:
```shell=
access
chdir
execve
exit
fork
free
getcwd
kill
localeconv
malloc
perror
read
waitpid
write
```

#### General Architecture

Minishell is organized in modules.

Main modules are:

- `Input` handles input and display prompt.

- `Lex` performs lexical analysis and is composed of two submodules: `Expansions` and `Separators`.

- `Synt` performs a syntactic analysis.

- `Jcont` arranges and execution of jobs.

- `Job` executes jobs i.e. commands. It has a submodule `Builtins`.

- `Transv` is a transverse module giving access to two submodules: `Signals` and `Error`.

#### Workflow

The following is the main steps of the minishell workflow, it is close to the way modules are organized:

- Input Stream

- Lexical Analysis

- Parsing

- Job control

- Job execution

After the input stream has been capture by the `Input module`, a raw string is passed to the `Lexer module` for lexical analysis. Then the tokenization process takes place.

Once the tokens created and subsitution of expansions done, the lexer send a table of pointer - containing the tokens - to the `Syntactic Module` for parsing. The parsing only checks unfitting/unrecognized tokens.

Once the syntactic analysis done the parser send the validated table of pointers to the `Job Control Module`. The job control then create sequences that are being executed by the `Job Module` in sequence.

Input sample : `ls -l -- file repo ; echo $? ; env -i ls ; coco ";s;s'"`

Fom the sample input, the first sequence executed by job would be `ls -l -- file repo`, the second sequence `echo $?` the third sequence `env -i ls`, then the last sequences `coco`, `s`, `s'"``

Unfortunately Minishell input does not recognized parenthethis nor brackets nor quotes as bash does.

Illustration of the above-explained workflow:

![Modules Flowchart](./tools/flowcharts/modules_flowchart.jpg)

## Usage

- Clone project repository

```shell=
git clone --recurse-submodules https://github.com/Ant0wan/Minishell.git
```

- Build project

```shell=
cd Minishell && make -j
```

- Run `minishell`

```shell=
./minishell
```

## Tests

- To perform test on the `minishell` execute the following command in your shell:

```shell=
make test
```
