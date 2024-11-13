#include "minishell.h"

int	g_signal;

static t_tokens	*keep_parsing(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_tokens	*t;

	if (!handle_quotes(tokens, shell))
		return (NULL);
	assign_types(&tokens);
	if (has_sintax_error(tokens, shell))
		return (NULL);
	if (process_tokens(&tokens, shell))
		return (NULL);
	temp = tokens;
	tokens = skip_redirects(tokens);
	while (temp)
	{
		t = temp->next;
		free(temp);
		temp = t;
	}
	return (tokens);
}

static void	routine1(t_shell *shell, char **buff)
{
	signals();
	*buff = readline("minishell: ");
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
	}
}

static void	routine2(t_tokens **tokens, t_shell *shell, char **buff)
{
	execute(tokens, shell);
	if (shell->fds)
		free_fds(shell);
	lstclear(tokens);
	free(*buff);
}

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
		tokens = keep_parsing(tokens, shell);
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
