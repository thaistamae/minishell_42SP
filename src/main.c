/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:31:23 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 01:31:23 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_syntax_error(t_shell *shell, char *line)
{
	printf("minishell: syntax error\n");
	shell->exit_status = 2;
	free(line);
	return (1);
}

static void	process_command(t_shell *shell, t_env *env, t_token *tokens)
{
	t_command	*cmd;

	if (!validate_syntax(tokens))
	{
		printf("minishell: syntax error\n");
		shell->exit_status = 2;
		return ;
	}
	cmd = parser(tokens);
	if (cmd)
	{
		shell->exit_status = execute_command(cmd, env);
		free_commands(cmd);
	}
}

static void	shell_loop(t_shell *shell, t_env *env)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*line)
			add_history(line);
		if (has_invalid_chars(line) || has_unclosed_quotes(line))
			if (handle_syntax_error(shell, line))
				continue ;
		tokens = lexer(line, shell);
		if (!tokens)
			if (handle_syntax_error(shell, line))
				continue ;
		process_command(shell, env, tokens);
		free_tokens(tokens);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_env	*env;

	(void)ac;
	(void)av;
	shell.envp = envp;
	shell.exit_status = 0;
	shell.tokens = NULL;
	env = init_env(envp);
	if (!env)
	{
		ft_putstr_fd("minishell: env init failed\n", STDERR_FILENO);
		return (1);
	}
	setup_signals_interactive();
	shell_loop(&shell, env);
	return (shell.exit_status);
}
