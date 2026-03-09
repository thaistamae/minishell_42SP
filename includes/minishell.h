#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type 	type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}   t_redir;

typedef	struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct	s_command	*next; 
}	t_command;

typedef struct s_builder
{
	char	*buffer;
	int		len;
	int		cap;
}	t_builder;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
	t_token	*tokens;
}	t_shell;

t_token	*new_token(char *value, t_token_type type);
void	add_token_back(t_token **list, t_token *new);
void	free_tokens(t_token *list);

void 	append_char(char **buffer, int *len, int *cap, char c);

t_token *lexer(char *line, t_shell *shell);
void	handle_word(char *line, int *i, t_token **list, t_shell *shell);
void	handle_dollar(char *line, int *i, t_builder *b, t_shell *shell);
void 	print_tokens(t_token *list);

#endif