/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:04:07 by albbermu          #+#    #+#             */
/*   Updated: 2025/04/11 14:41:18 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *str, t_mini *shell)
{
	t_env	*env_var;

	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(shell->exit_code));
	if (str[0] == '$' && str[1])
	{
		env_var = get_env(shell->env, &str[1]);
		if (env_var && env_var->value)
			return (ft_strdup(env_var->value));
		return (ft_strdup(""));
	}
	return (ft_strdup(str));
}
