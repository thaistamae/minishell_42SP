/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:44:18 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/25 22:57:25 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int			builtin_echo(t_command *cmd);
int			builtin_pwd(void);
int			builtin_env(t_env *env);
int			builtin_cd(t_command *cmd, t_env *env);
int			builtin_exit(t_command *cmd);
int			builtin_export(t_command *cmd, t_env *env);
int			builtin_unset(t_command *cmd, t_env *env);

#endif