#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[17];

	str[0] = "%s: Command not found\n";
	str[1] = "bash: %s: %s: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: Makefile: Not a directory\n";
	return (str[i]);
}

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

char	*get_var(char *token)
{
	int		i;

	i = 1;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\"' || token[i] == '\'')
			break ;
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*trim_quotes(char *token, const char *quote_type, bool *sq, bool *dq)
{
	char	*temp;
	int		i;

	i = ft_strclen(&token[1], quote_type[0]);
	if (ft_strclen(token, '$') && ft_strclen(token, '$') > i)
	{
		if (quote_type[0] == '\"')
			dq = false;
		else if (quote_type[0] == '\'')
			sq = false;
	}
	temp = ft_strdup(token);
	temp[i + 1] = '\0';
	temp = ft_strtrim(temp, quote_type);
	token = ft_strjoin(temp, token + i + 2);
	free(temp);
	return (token);
}

t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*ret;
	char	*token;
	char	*temp;
	char	*envp_var;
	bool	dq;
	bool	sq;
	int		i;

	ret = tokens;

	sq = false;
	dq = false;
	while (tokens && tokens->token)
	{
		sq = false;
		dq = false;
		token = tokens->token;
		i = 0;
		while (token[i])
		{
			if (token[i] == '\'' && dq == false)
			{
				sq = !sq;
				char *trimed = trim_quotes(&token[i], "\'", &sq, &dq);
				token[i] = '\0';
				token = ft_strjoin(token, trimed);
				continue ;
			}
			else if (token[i] == '\"' && sq == false)
			{
				dq = !dq;
				char *trimed = trim_quotes(&token[i], "\"", &sq, &dq);
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
				token = ft_strjoin(token, handle_expander(shell->envp, envp_var));
				token = ft_strjoin(token, temp);
				free(temp);
				free(envp_var);
				i = 0;
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
	shell.envp = envp;
	shell.last_path = ft_strdup(getenv("PWD"));
	shell.original_stdin = dup(STDIN_FILENO);
	shell.original_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (!*input_buffer)
			continue ;
		if (!ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))
		{
			printf("exit\n");
			break ;
		}
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		process_tokens(&tokens, &shell); // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
		tokens = skip_redirects(tokens);
		tokens = handle_quotes(tokens, &shell);
		// find_expander(tokens, shell.envp);
		if (shell.fd_in != -1 && shell.fd_out != -1)
			execute(tokens, &shell);
		// else printa erro
		dup2(shell.original_stdin, STDIN_FILENO);
		lstclear(&tokens);
	}
	free_all(tokens, &shell, input_buffer);
}
