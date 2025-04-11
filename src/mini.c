/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:48:31 by fefa              #+#    #+#             */
/*   Updated: 2025/04/09 11:39:52 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_token(t_mini *shell, t_token *token)
{
	t_exec_cmd	exec;

	exec = (t_exec_cmd){0};
	create_exec_cmd(&exec, token);
	execute(shell, &exec);
	free_exec_cmd(&exec);
}

void	exec_start(t_mini *shell, t_token *token)
{
	while (token)
	{
		if (token->type == INPUT || token->type == TRUNC || token->type
			== APPEND)
		{
			redir(shell, token);
			token = token->next;
		}
		else if (token->type == CMD)
		{
			exec_token(shell, token);
			break ;
		}
		else
			token = token->next;
	}
}

void	get_next_cmd(t_token	**token)
{
	while (*token)
	{
		if ((*token)->type == CMD)
			return ;
		*token = (*token)->next;
	}
}

void	exec_sort_token(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;

	token = cmd->tokens;
	get_next_cmd(&token);
	while (!shell->exit && token)
	{
		exec_start(shell, token);
		token = token->next;
		get_next_cmd(&token);
	}
}

void	minishell(t_mini *shell)
{
	t_cmd	*current;

	current = shell->cmd;
	while (!shell->exit && current)
	{
		exec_sort_token(shell, current);
		current = current->next;
	}
}
