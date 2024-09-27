#include "minishell.h"

char	*handle_input(t_tokens **tokens)
{
	t_tokens	*temp;
	char		infile;
	int			has_infile;

	temp = *tokens;
	has_infile = 0;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			infile = temp->token;
			has_infile = 1;
		}
		temp = temp->next;
	}
	if (has_infile == 0)
	{
		temp = *tokens;
		while (temp)
		{
			if (temp->type == LIMITER)
				; //TODO: implement heredoc
		//duvida - o que faco se nao tiver input nenhum? nada ? o execve faz sozinho?
			temp = temp->next;
		}
		return (NULL);
	}
	else
		return (infile);
}

char	**join_cmd_args(t_tokens **tokens)
{
	t_tokens *temp;
	int	j;
	int n;
	char **cmds;
	char *temp1;

	temp = *tokens;
	j = 0;
	n = count_pipes(tokens);
	cmds = malloc((n + 1) * sizeof(char *) + 1);
	//TODO: protecao malloc
	while (temp)
	{
		if (temp->type == CMD)
			cmds[j] = strdup(temp->token);
		else if (temp->type == ARG)
		{
			temp1 = cmds[j];
			cmds[j] = ft_strjoin(cmds[j], temp->token);
			free(temp1);
		}
		else if (temp->type == PIPE)
			j++;
		temp = temp->next;
	}
	cmds[j] = 0;
	return (cmds);
}

void	process_tokens(t_tokens **tokens)
{
	t_tokens *temp;
	char	*infile;
	char	*outfile;
	char	**cmds;

	infile = handle_input(tokens);
	cmds = join_cmd_args(tokens);
	temp = *tokens;
	while (temp)
	{
		if (temp->type == OUTPUT)
		{
			outfile = temp->token;
			break ;
		}
		temp = temp->next;
	}
	if (count_pipes(tokens)) 
		;//pipe_handling(); //TODO: pipes handling
	else
	{
		process_full_path(cmds[0], (*tokens)->env);
		//exec_cmd(); //TODO: Check if is builtin or execve
	}
}
