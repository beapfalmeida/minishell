/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:43 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/03 10:40:03 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

/// @brief After tokens list created, treat all the tokens: 
// quotes, types, syntax errors, redirects, ...
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
/// @return New tokens list.
static t_tokens	*keep_parsing(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_tokens	*t;
	int			ret;

	if (!handle_quotes(*tokens, shell))
		return (lstclear(tokens, 1), NULL);
	ret = assign_types(tokens);
	if (ret)
		return (do_error(0, *tokens, shell, ret),
			lstclear(tokens, 1), NULL);
	if (has_sintax_error(*tokens, shell))
		return (lstclear(tokens, 1), NULL);
	if (process_tokens(tokens, shell))
		return (lstclear(tokens, 1), NULL);
	temp = *tokens;
	*tokens = skip_redirects(*tokens);
	if (!*tokens)
		free_fds(shell);
	while (temp)
	{
		t = temp->next;
		free(temp);
		temp = t;
	}
	return (*tokens);
}

/// @brief Reads the line input, checks for SIGINT (Ctrl-C)
/// @param shell Pointer to the shell vars struct
/// @param buff Pointer to the location where the line 
// read by readline() will be stored.
static void	routine1(t_shell *shell, char **buff)
{
	signals();
	*buff = readline("minishell: ");
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
	}
	if (!*buff)
		ft_printf_fd(STDOUT_FILENO, "exit\n");
}

/// @brief Execute and clear everything.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct
/// @param buff Pointer to the location where the line 
// read by readline() will be stored.
static void	routine2(t_tokens **tokens, t_shell *shell, char **buff)
{
	execute(tokens, shell);
	if (shell && shell->fds)
		free_fds(shell);
	lstclear(tokens, 1);
	free(*buff);
}

/// @brief Main loop function.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
/// @param input_buffer Pointer to the location where the line 
// read by readline() will be stored.
void	minishell(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	int	check_exit;

	while (1)
	{
		routine1(shell, &input_buffer);
		if (!input_buffer)
			break ;
		if (input_buffer && !*input_buffer)
			continue ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer);
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		tokens = keep_parsing(&tokens, shell);
		if (!tokens)
			continue ;
		check_exit = check_exit_exec(&tokens, shell, input_buffer);
		if (check_exit == 2)
			continue ;
		else if (check_exit == 1)
			break ;
		routine2(&tokens, shell, &input_buffer);
	}
}

/// @brief Main function.
/// @param argc Not used.
/// @param argv  Not used.
/// @param envp Pointer to the environment variables array.
/// @return 0
int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	t_shell		shell;
	char		*input_buffer;

	(void)argc;
	(void)argv;
	tokens = NULL;
	input_buffer = NULL;
	init_shell(&shell, envp);
	minishell(tokens, &shell, input_buffer);
	free_all(&tokens, &shell, input_buffer);
	exit(shell.exit_code);
}
