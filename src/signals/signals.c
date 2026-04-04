/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:45:37 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/04 11:50:22 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handler para SIGINT no shell interativo (Ctrl+C)
static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// handler para SIGQUIT no shell interativo (Ctrl+\\)
static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// configura sinais para o shell interativo
void	setup_signals_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTERM, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

// configura sinais para processos filhos
void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
