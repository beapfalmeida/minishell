#include "minishell.h"

int g_signal;

static t_tokens	*keep_parsing(t_tokens *tokens, t_shell *shell)
{
	t_tokens *temp;
	t_tokens *t;
	handle_quotes(tokens, shell);
	
	// if (*tokens->token == '\0')
	// 	return (NULL);
	assign_types(&tokens);
	//print_tokens(&tokens);
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



static int check_exit_exec(t_tokens **tokens, t_shell *shell, char *input_buffer)
{
	if (shell->interrupt_exec == true)
		{
			shell->interrupt_exec = false;
			free_all(*tokens, shell, input_buffer);
			return (2);
		}
	if (ft_strlen((*tokens)->token) && !ft_strncmp((*tokens)->token, "exit", 4))
	{
		if (*tokens && (*tokens)->next)
			shell->exit_code = calculate_exit_code(*tokens, (*tokens)->next->token);
		if ((*tokens)->next->next && shell->exit_code != 2)
		{
			ft_printf_fd(2, "bash: exit: too many arguments\n");
			shell->exit_code = 1;
			lstclear(tokens);
			free(input_buffer);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

void	minishell(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	int	check_exit;
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (g_signal == SIGINT)
		{
			shell->exit_code = 130;
			g_signal = 0;
		}
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
		execute(tokens, shell);
		lstclear(&tokens);
		free(input_buffer);
		// dup2(STDIN_FILENO, shell->original_stdin);
		// dup2(STDOUT_FILENO, shell->original_stdout);
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
	free_all(tokens, &shell, input_buffer);
	exit(shell.exit_code);
}
