# Minishell MVP

Versão minimalista do minishell com funcionalidades básicas.

## Funcionalidades

- **Builtin**: `echo` - imprime argumentos na tela
- **Builtin**: `exit` - sai do shell
- **Comandos externos**: executa qualquer comando do sistema (ls, cat, grep, etc.)

## Compilar

```bash
make
```

## Executar

```bash
./minishell_mvp
```

## Exemplos de uso

```bash
minishell> echo Hello World
Hello World
minishell> ls -la
[lista arquivos do diretório atual]
minishell> cat README.md
[exibe conteúdo do arquivo]
minishell> exit
```
