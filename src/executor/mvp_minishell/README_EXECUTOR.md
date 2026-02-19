# Como desenvolver o Executor sem depender do Parser

## Estratégia

O executor recebe uma estrutura `t_command`:
```c
typedef struct s_command
{
	char            **args;      // Array de argumentos ["ls", "-la", NULL]
	t_redir         *redirs;     // Lista encadeada de redirecionamentos
	struct s_command *next;      // Próximo comando (para pipes)
} t_command;
```

Desenvolvendo sem o parser:

## Funções auxiliares criadas

### `create_simple_command()`
Cria um comando simples com até 3 argumentos:
```c
t_command *cmd = create_simple_command("ls", "-la", NULL);
// Cria: {args: ["ls", "-la", NULL], redirs: NULL, next: NULL}
```

### `create_redirect()`
Cria um redirecionamento:
```c
t_redir *redir = create_redirect(T_REDIRECT_OUT, "output.txt");
```

### `add_redirect()`
Adiciona redirecionamento a um comando:
```c
add_redirect(cmd, redir);
```

## Como usar

### 1. Compilar o teste:
```bash
cd mvp_minishell
cc -Wall -Wextra -Werror test_executor.c -o test_executor
```

### 2. Executar:
```bash
./test_executor
```

### 3. Desenvolver o executor

No arquivo real do executor (`src/executor/executor.c`), você pode:

1. Copiar as funções auxiliares de criação de mock
2. Criar testes específicos para cada funcionalidade
3. Implementar o executor step-by-step:
   - Primeiro: executar comando simples
   - Depois: adicionar redirecionamentos
   - Depois: adicionar pipes
   - Por último: adicionar builtins

## Exemplo de desenvolvimento incremental

### Fase 1: Executor básico
```c
void execute_command(t_command *cmd)
{
	pid_t pid = fork();
	if (pid == 0)
		execvp(cmd->args[0], cmd->args);
	else
		waitpid(pid, NULL, 0);
}
```

### Fase 2: Adicionar builtins
```c
if (is_builtin(cmd->args[0]))
	execute_builtin(cmd);
else
	execute_external(cmd);
```

### Fase 3: Adicionar redirecionamentos
```c
apply_redirections(cmd->redirs);
execvp(cmd->args[0], cmd->args);
```

### Fase 4: Adicionar pipes
```c
while (cmd->next)
{
	pipe(pipefd);
	// conectar comandos...
}
```

## Pontos positivos

✅ Desenvolve o executor de forma independente
✅ Testa cada funcionalidade isoladamente
✅ Não precisa esperar o parser ficar pronto
✅ Facilita debug e identificação de problemas
✅ Permite TDD (Test-Driven Development)
