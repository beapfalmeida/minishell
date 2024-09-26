#include "minishell.h"

int main()
{
	t_tokens	*tokens = NULL;
	char	*input_buffer;

	input_buffer = readline("minishell: ");
	// if (ft_strnstr(input_buffer, "\n", ft_strlen(input_buffer)))
	// 	write(1, "minishell: ", 11);
	if (input_buffer && *input_buffer)
		add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
	create_tokens(&tokens, input_buffer);
	exec_cmd(tokens);
	free(input_buffer);
	free(tokens->token);
}