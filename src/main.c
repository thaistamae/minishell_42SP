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
// int main(void)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if(!line)
// 			break;
// 		if(*line)
// 			add_history(line);
// 		free(line);
// 	}
// 	return (0);
// }

// ...existing code...
static t_command	*build_test_pipeline(void)
{
    t_command	*cmd1;
    t_command	*cmd2;

	cmd1 = ft_calloc(1, sizeof(t_command));
    cmd2 = ft_calloc(1, sizeof(t_command));
    cmd1->args = ft_calloc(2, sizeof(char *));
    cmd1->args[0] = ft_strdup("/bin/ls");
    cmd1->next = cmd2;
    cmd2->args = ft_calloc(3, sizeof(char *));
    cmd2->args[0] = ft_strdup("/usr/bin/wc");
    cmd2->args[1] = ft_strdup("-l");
    return (cmd1);
}

int	main(int ac, char **av, char **envp)
{
    t_shell		shell;
    t_command	*cmd;

    (void)ac;
    (void)av;
    shell.envp = envp;
    shell.exit_status = 0;
    cmd = build_test_pipeline();
    shell.exit_status = execute_command(cmd, NULL);
    /* TODO: liberar cmd e args */
    return (shell.exit_status);
}