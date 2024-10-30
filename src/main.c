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
	if (has_sintax_error(tokens, shell))
		return (NULL);
	if (process_tokens(&tokens, shell)) // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
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

static void	init_shell(t_shell *shell, char **envp)
{
	char	**envp_array;
	int		i;

	envp_array = malloc((arr_len(envp) + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		envp_array[i] = ft_strdup(envp[i]);
		if (!envp_array[i])
			free_array(&envp_array[i], i);
		i++;
	}
	envp_array[i] = NULL;
	shell->envp = envp_array;
	shell->exit_code = 0;
	shell->last_path = ft_strdup(getenv("PWD"));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	shell->interrupt_exec = false;
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
		check_exit = check_exit_exec(&tokens, shell, input_buffer);
		if (check_exit == 2)
			continue ;
		else if (check_exit == 1)
			break ;
		// if (tokens)	// Voltei a colocar assim pois se for if (!tokens): continue,  ele nao faz o dup2 de volta para o stdin_original e le do fd do heredoc na proxima readline
		execute(tokens, shell);
		lstclear(&tokens);
		free(input_buffer);
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
