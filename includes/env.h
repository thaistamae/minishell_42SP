/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:33:50 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 16:33:53 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "structs.h"

t_env	*init_env(char **envp);
int		set_env_var(t_env **env, const char *key, const char *value);
int		unset_env_var(t_env **env, const char *key);
char	*get_env_value(t_env *env, const char *key);

#endif
