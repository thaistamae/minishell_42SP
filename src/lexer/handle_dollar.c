#include "minishell.h"
#include "libft.h"

//Busca o valor de uma variável de ambiente no envp
//Retorna apenas a parte após o '='
static char	*get_env_value(char *var, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len)
			&& envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

//Adiciona uma string inteira ao buffer do builder
static void	append_str(t_builder *b, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		append_char(&b->buffer, &b->len, &b->cap, str[j]);
		j++;
	}
}

//Lida com a expansão da variável especial $?
//Adiciona o exit_status atual do shell ao buffer
static int	handle_exit_status(char *line, int *i, 
								t_builder *b, t_shell *shell)
{
	char	*status;

	if (line[*i] != '?')
		return (0);
	status = ft_itoa(shell->exit_status);
	if (!status)
		return (1);
	append_str(b, status);
	free(status);
	(*i)++;
	return (1);
}

//Lê o nome de uma variável de ambiente após o '$'
//Busca seu valor no envp e adiciona ao buffer
static void	handle_env_var(char *line, int *i,
							t_builder *b, t_shell *shell)
{
	int		start;
	char	*var;
	char	*value;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var = ft_substr(line, start, *i - start);
	if (!var)
		return ;
	value = get_env_value(var, shell->envp);
	if (value)
		append_str(b, value);
	free(var);
}

//Lida com a expansão de variáveis iniciadas por '$'
//Pode expandir $?, variáveis de ambiente ou tratar '$' literal
void	handle_dollar(char *line, int *i,
					t_builder *b, t_shell *shell)
{
	(*i)++;
	if (handle_exit_status(line, i, b, shell))
		return ;
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
	{
		append_char(&b->buffer, &b->len, &b->cap, '$');
		return ;
	}
	handle_env_var(line, i, b, shell);
}
