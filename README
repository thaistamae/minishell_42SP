*This project has been created as part of the 42 curriculum by kaidda-s and ttamae.*

# Minishell

## Description

Minishell is a lightweight implementation inspired by the original Bash shell.
The goal of this project is to understand how a shell works by handling user input, parsing commands, and executing them with proper process and file descriptor management.

The work was divided between two main components: the parser and executor.

### Parser  
Focused on **tokenizing and parsing user input**, handling quotes, spaces, pipes, and redirections correctly.  

### Executor
Focused on **executing commands**, managing processes, handling built-in commands, and implementing file descriptor redirections.  

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable `minishell`.

You can also use the following commands:

- `make clean`- Removes object files.

- `make fclean` - Removes object files and the executable.

- `make re` - Recompiles the project.

### Execution

To run the shell:

```bash
./minishell
```

After launching, a prompt will be displayed:

```bash
minishell$
```

You can then:

* Execute commands (e.g. `ls`, `echo hello`)
* Use environment variables (e.g. `echo $PATH`)
* Use pipes (e.g. `ls | grep .c`)
* Use redirections (e.g. `echo hello > file.txt`)
* Use input redirection and heredoc (e.g. `cat < file.txt`, `cat << EOF`)

To exit the shell, you can:

```bash
exit
```

or press `Ctrl+D`.

## Resources

* The default shell (e.g., Bash) was used to observe and understand the expected behavior of commands, prompts, and redirections.
* We referred to architectural guides such as ["Minishell: A Comprehensive Guide"](https://medium.com/@august1.caes/minishell-a-comprehensive-guide-24cb30a342ec), which breaks down core components like the main loop, parser, executor, signal handlers, and environment management.
* Artificial Intelligence (AI) tools were used to assist with testing debugging, and exploring possible improvements during the development of this project.