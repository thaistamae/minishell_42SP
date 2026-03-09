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