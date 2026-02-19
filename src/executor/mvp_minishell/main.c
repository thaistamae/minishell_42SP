//Minimo produto viavel (MVP)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

void	ft_echo(char **args)
{
	int	i = 1;

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	execute_external(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		// Processo filho
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(1);
		}
	}
	else
	{
		// Processo pai
		waitpid(pid, &status, 0);
	}
}

void	parse_and_execute(char *input)
{
	char	*args[MAX_ARGS];
	char	*token;
	int		i = 0;

	token = strtok(input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (!args[0])
		return;

	// Builtin: echo
	if (strcmp(args[0], "echo") == 0)
		ft_echo(args);
	// Builtin: exit
	else if (strcmp(args[0], "exit") == 0)
		exit(0);
	// Comando externo
	else
		execute_external(args);
}

int	main(void)
{
	char	input[MAX_INPUT];

	while (1)
	{
		printf("minishell> ");
		fflush(stdout);

		if (!fgets(input, MAX_INPUT, stdin))
			break;

		parse_and_execute(input);
	}

	printf("exit\n");
	return (0);
}
