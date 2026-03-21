#include "minishell.h"

//Método apenas para testes
void print_tokens(t_token *list)
{
	while (list)
	{
		printf("TOKEN: %-10s TYPE: %d\n", list->value, list->type);
		list = list->next;
	}
}

void	print_redirs(t_redir *r)
{
	while (r)
	{
		printf(" redir type: %d file: %s\n", r->type, r->file);
		r = r->next;
	}
}

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("COMMAND\n");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf(" arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		print_redirs(cmd->redirs);
		cmd = cmd->next;
	}
}

