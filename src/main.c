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
#include "executor.h"
#include "structs.h"
#include "signal.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

static void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

static void	shell_loop(t_shell *shell, t_env *env)
{
	char		*line;
	t_token		*tokens;
	t_command	*cmd;

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
		tokens = lexer(line, shell);
		if (tokens)
		{
			cmd = parser(tokens);
			if (cmd)
			{
				shell->exit_status = execute_command(cmd, env);
				free_commands(cmd);
			}
			free_tokens(tokens);
		}
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
