#include "minishell.h"

t_token *new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void add_token_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if(!*list)
	{
		*list = new;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;	
}

void free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}
