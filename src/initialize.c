/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:35:35 by fefa              #+#    #+#             */
/*   Updated: 2025/04/09 11:33:29 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_end(t_cmd **first, t_cmd *new)
{
	t_cmd	*tmp;

	if (!(*first))
	{
		*first = new;
		return ;
	}
	tmp = *first;
	while (tmp ->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	create_node_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	*cmd = new;
	new->cmd = str;
	new->words = ft_split_special(str, " ");
	new->next = NULL;
	new->tokens = NULL;
	create_tokens(new);
}

void	create_cmd(char *input, t_mini *shell)
{
	t_cmd	*cmd;
	char	**array;
	size_t	i;

	i = 0;
	array = ft_split_special(input, ";");
	if (!array)
		return ;
	while (array[i])
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
		{
			perror("malloc failed");
			free_array(array);
			return ;
		}
		cmd->cmd = ft_strdup(array[i]);
		if (!cmd->cmd)
		{
			perror("ft_strdup failed");
			free(cmd);
			free_array(array);
			return ;
		}
		cmd->words = ft_split_special(array[i], " ");
		cmd->next = NULL;
		cmd->tokens = NULL;
		create_tokens(cmd);
		add_cmd_end(&shell->cmd, cmd);
		free(array[i]);
		i++;
	}
	free(array);
}

void	create_exec_cmd(t_exec_cmd *exec, t_token *token)
{
	t_token	*tmp;
	int		arg_count;

	arg_count = 0;
	exec->args = NULL;
	exec->cmd = NULL;
	tmp = token->next;
	while (tmp && tmp->type == ARG)
	{
		arg_count++;
		tmp = tmp->next;
	}
	exec->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!exec->args)
	{
		perror("malloc failed");
		return ;
	}
	tmp = token->next;
	arg_count = 0;
	while (tmp && tmp->type == ARG)
	{
		exec->args[arg_count] = ft_strdup(tmp->str);
		if (!exec->args[arg_count])
		{
			perror("ft_strdup failed");
			free_array(exec->args);
			exec->args = NULL;
			return ;
		}
		arg_count++;
		tmp = tmp->next;
	}
	exec->args[arg_count] = NULL;
	exec->cmd = ft_strdup(token->str);
	if (!exec->cmd)
	{
		perror("ft_strdup failed");
		free_array(exec->args);
		exec->args = NULL;
		return ;
	}
}

void	init(t_mini *shell, char **env)
{
	shell->fdin = STDIN_FILENO;
	shell->fdout = STDOUT_FILENO;
	shell->cmd = NULL;
	shell->arr_env = NULL;
	shell->env = NULL;
	shell->secret = NULL;
	ft_cpy_arr_env(&shell->arr_env, env);
	ft_cpy_env(&shell->env, shell->arr_env);
	ft_cpy_env(&shell->secret, shell->arr_env);
	reset_fds(shell, 0);
	(void)env;
	shell->exit = 0;
}
