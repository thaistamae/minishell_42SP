#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Estruturas mockadas do minishell
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}   t_redir;

typedef	struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct	s_command	*next; 
}	t_command;

// ===== FUNÇÕES AUXILIARES PARA CRIAR t_command MOCK =====

t_command	*create_simple_command(char *cmd, char *arg1, char *arg2)
{
	t_command	*command;
	int			argc = 0;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);

	// Contar argumentos
	if (cmd) argc++;
	if (arg1) argc++;
	if (arg2) argc++;

	// Alocar array de args
	command->args = malloc(sizeof(char *) * (argc + 1));
	if (!command->args)
	{
		free(command);
		return (NULL);
	}

	// Preencher args
	argc = 0;
	if (cmd) command->args[argc++] = strdup(cmd);
	if (arg1) command->args[argc++] = strdup(arg1);
	if (arg2) command->args[argc++] = strdup(arg2);
	command->args[argc] = NULL;

	command->redirs = NULL;
	command->next = NULL;

	return (command);
}

t_redir	*create_redirect(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);

	redir->type = type;
	redir->file = strdup(file);
	redir->next = NULL;

	return (redir);
}

void	add_redirect(t_command *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return;
	}

	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = redir;
}

void	free_command(t_command *cmd)
{
	t_redir	*redir;
	t_redir	*tmp;
	int		i;

	if (!cmd)
		return;

	// Liberar args
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}

	// Liberar redirs
	redir = cmd->redirs;
	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}

	free(cmd);
}

// ===== EXECUTOR SIMPLES =====

void	execute_command(t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return;

	printf("Executando: %s", cmd->args[0]);
	int i = 1;
	while (cmd->args[i])
		printf(" %s", cmd->args[i++]);
	printf("\n");

	// Builtin simples: echo
	if (strcmp(cmd->args[0], "echo") == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
		return;
	}

	// Comando externo
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		// TODO: Aplicar redirecionamentos aqui
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			perror("execvp");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

// ===== TESTES =====

void	test_simple_command(void)
{
	t_command	*cmd;

	printf("\n=== Teste 1: Comando simples (ls -la) ===\n");
	cmd = create_simple_command("ls", "-la", NULL);
	execute_command(cmd);
	free_command(cmd);
}

void	test_builtin_echo(void)
{
	t_command	*cmd;

	printf("\n=== Teste 2: Builtin echo ===\n");
	cmd = create_simple_command("echo", "Hello", "World");
	execute_command(cmd);
	free_command(cmd);
}

void	test_external_command(void)
{
	t_command	*cmd;

	printf("\n=== Teste 3: Comando externo (pwd) ===\n");
	cmd = create_simple_command("pwd", NULL, NULL);
	execute_command(cmd);
	free_command(cmd);
}

void	test_with_redirect(void)
{
	t_command	*cmd;
	t_redir		*redir;

	printf("\n=== Teste 4: Comando com redirecionamento (estrutura pronta) ===\n");
	cmd = create_simple_command("echo", "teste", NULL);
	redir = create_redirect(T_REDIRECT_OUT, "output.txt");
	add_redirect(cmd, redir);

	printf("Comando: %s %s > %s\n", cmd->args[0], cmd->args[1], cmd->redirs->file);
	printf("(Redirecionamento ainda não implementado no executor)\n");

	free_command(cmd);
}

int	main(void)
{
	printf("====================================\n");
	printf("   TESTES DO EXECUTOR (SEM PARSER)\n");
	printf("====================================\n");

	test_builtin_echo();
	test_simple_command();
	test_external_command();
	test_with_redirect();

	printf("\n=== Todos os testes concluídos ===\n");
	return (0);
}
