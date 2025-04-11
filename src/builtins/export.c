/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:34:52 by fefa              #+#    #+#             */
/*   Updated: 2025/04/09 12:09:47 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	print_export_sort(t_env *secret)
{
	t_env	*cpy;
	t_env	*smallest;
	t_env	*printed;

	printed = NULL;
	while (1)
	{
		cpy = secret;
		smallest = NULL;
		while (cpy)
		{
			if ((!smallest || ft_strcmp(cpy->key, smallest->key) < 0) && \
				(!printed || ft_strcmp(printed->key, cpy->key) < 0))
				smallest = cpy;
			cpy = cpy->next;
		}
		if (!smallest)
			return (SUCCESS);
		printed = smallest;
		if (printed->key)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(printed->key, STDOUT_FILENO);
			if (printed->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(printed->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
            }
            ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	return (ERROR);
}

bool	ft_export(char *arg, t_env *env, t_env *secret)
{
	t_env	*new;
	t_env	*old;

	if (!arg || !arg[0])
		return (print_export_sort(secret));
	create_node_env(&new, arg);
	if (!is_valid_env_node(*new))
	{
		free_node(new);
		return (ERROR);
	}
	old = get_env(env, new->key);
	if (old)
	{
		update_node(old, ft_strdup(new->value));
		free_node(new);
		return (SUCCESS);
	}
	add_env_end(&env, new);
	add_env_end(&secret, new);
	return (SUCCESS);
}
