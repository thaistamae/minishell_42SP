#include "minishell.h"

//vai percorrer os tokens e montar a lista linkada com os comandos 
//os comandos são separados em listas de argumentos e lista de redirects
t_command	*parse_commands(t_token *tokens)
{
	t_command	*head;
	t_command	*current;

	head = new_command();
	if (!head)
		return (NULL);
	current = head;
	while (tokens)
	{
		if (tokens->type == T_WORD)
			add_arg(current, tokens->value);
		else if (is_redirection(tokens->type))
			parser_handle_redirection(current, &tokens);
		else if (tokens->type == T_PIPE)
		{
			current->next = new_command();
			current = current->next;
		}
		tokens = tokens->next;
	}
	return (head);
}