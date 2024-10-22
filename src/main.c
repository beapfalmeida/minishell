#include "minishell.h"

int g_signal;

static void	free_all(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	if (input_buffer)
		free(input_buffer);
	if (shell->last_path)
		free(shell->last_path);
	if (tokens)
		lstclear(&tokens);
	close(shell->original_stdin);
	close(shell->original_stdout);
}

static t_tokens	*keep_parsing(t_tokens *tokens, t_shell *shell)
{
	t_tokens *temp;
	handle_quotes(tokens, shell);
	if (*tokens->token == '\0')
		return (NULL);
	assign_types(&tokens);
	process_tokens(&tokens, shell); // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
	temp = tokens;
	tokens = skip_redirects(tokens);
	lstclear(&temp);
	return (tokens);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_code = "0";
	shell->last_path = ft_strdup(getenv("PWD"));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
}

char	*get_var(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\"' || token[i] == '\'')
			break ;
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*skip_quote(char *token, const char *quote_type, bool *sq, bool *dq, bool *first_encounter)
{
	char	*ret;

	ret = ft_strdup(token);
	if (quote_type[0] == '\'' && *sq == true && *first_encounter == false)
		*sq = false;
	else if (quote_type[0] == '\"' && *dq == true && *first_encounter == false)
		*dq = false;
	*first_encounter = false;
	ret++;
	return (ret);
}
//TODO: free string_joins
t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*ret;
	char	*token;
	char	*temp;
	char	*envp_var;
	bool	dq;
	bool	sq;
	bool	first_encounter;
	int		i;

	ret = tokens;

	sq = false;
	dq = false;
	first_encounter = true;
	while (tokens && tokens->token)
	{
		sq = false;
		dq = false;
		first_encounter = true;
		token = tokens->token;
		i = 0;
		while (token[i])
		{
			first_encounter = true;
			if (token[i] == '\'' && dq == false)
			{
				sq = !sq;
				char *trimed = skip_quote(&token[i], "\'", &sq, &dq, &first_encounter);
				token[i] = '\0';
				token = ft_strjoin(token, trimed);
				continue ;
			}
			else if (token[i] == '\"' && sq == false)
			{
				dq = !dq;
				char *trimed = skip_quote(&token[i], "\"", &sq, &dq, &first_encounter);
				token[i] = '\0';
				token = ft_strjoin(token, trimed);
				continue ;
			}
			if (token[i] == '$' && sq == false)
			{
				envp_var = get_var(ft_strdup(&token[i + 1]));
				temp = ft_strdup(&token[i + ft_strlen(envp_var) + 1]);
				token[i] = '\0';
				// Free token after strjoin
				token = ft_strjoin(token, handle_expander(shell->envp, envp_var, shell));
				i += ft_strlen(handle_expander(shell->envp, envp_var, shell));
				token = ft_strjoin(token, temp);
				free(temp);
				free(envp_var);
				continue ;
			}
			else
				i++;
		}
		tokens->token = token;
		tokens = tokens->next;
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens = NULL;
	t_shell		shell;
	char	*input_buffer;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (g_signal == SIGINT)
		{
			shell.exit_code = "130";
			g_signal = 0;
		}
		if (!input_buffer || (ft_strlen(input_buffer) && !ft_strncmp(input_buffer, "exit", 4)))
		{
			printf("exit\n");
			break ;
		}
		if (!*input_buffer)
			continue ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		tokens = keep_parsing(tokens, &shell);
		if (!tokens)
			continue ;
		execute(tokens, &shell);
		dup2(shell.original_stdin, STDIN_FILENO);
		lstclear(&tokens);
		free(input_buffer);
	}
	free_all(tokens, &shell, input_buffer);
}
