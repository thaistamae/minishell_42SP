#include "minishell.h"

//Por enquanto usada apenas para testar a tokenização
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	*line;
	t_shell	shell;

	shell.envp = envp;
	shell.exit_status = 0;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);

		shell.tokens = lexer(line, &shell);
		print_tokens(shell.tokens);

		free_tokens(shell.tokens);
		free(line);
	}
}