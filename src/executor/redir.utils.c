/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:17:05 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/11 01:56:16 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Guardar os fds originais antes de redirecionar
int save_std_fds(int *saved_stdin, int *saved_stdout);

// Voltar stdout/stdin aos valores originais
void restore_std_fds(int saved_stdin, int saved_stdout);

// Abrir arquivo para escrita (output)
int open_output_file(char *filename);