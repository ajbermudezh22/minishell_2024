/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:27:34 by fefa              #+#    #+#             */
/*   Updated: 2025/04/11 10:40:53 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_node_env(t_env	**node, char *str)
{
	t_env	*env;
	char	**array;

	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	array = ft_split(str, '=');
	if (!array)
	{
		free(env);
		return ;
	}
	env->key = ft_strdup(array[0]);
	if (!env->key)
	{
		free(env);
		free_array(array);
		return ;
	}
	env->value = NULL;
	join_into_str(&env->value, &array[1], "=");
	free_array(array);
	env->next = NULL;
	*node = env;
}

bool	is_valid_env_node(t_env node)
{
	if (!node.key || !ft_strcmp(node.key, ""))
		return (FALSE);
	if (ft_isdigit(node.key[0]))
		return (FALSE);
	if (node.key[0] == '=')
		return (FALSE);
	return (TRUE);
}

void	add_env_end(t_env **first, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!(*first))
	{
		*first = new;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
