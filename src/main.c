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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_shell		shell;
	t_command	*cmds;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	shell.exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (has_invalid_chars(line) || has_unclosed_quotes(line))
		{
			printf("minishell: syntax error\n");
			free(line);
			continue ;
		}
		tokens = lexer(line, &shell);
		print_tokens(tokens);
		if (!validate_syntax(tokens))
			printf("minishell: sintax error \n");
		else
		{
			cmds = parse_commands(tokens);
			print_commands(cmds);
		}		
		free_tokens(tokens);
		free_commands(cmds);
		free(line);
	}
	return (0);
}
