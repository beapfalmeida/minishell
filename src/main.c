#include "minishell.h"

void	parse(char *str)
{
	(void)str;
}


// int	main()
// {
// 	char *str;

// 	write(1, "minishell: ", 11);
// 	while (1)
// 	{
// 		//descobrir como se usa isto :)
// 		str = readline("minishell: ");
// 		if (ft_strnstr(str, "\n", ft_strlen(str)))
// 			write(1, "minishell: ", 11);
// 		if (!ft_strncmp(str, "exit", ft_strlen(str)))
// 			break ;
// 		parse(str);
// 		free(str);
// 	}
// 	free(str);
// }

///// PSEUDO CODIGO ////
/*
int main (void)
{
	char *line_buffer;
 	while (1)
 	{
		ft_signals();
			///// This is reading the signals ctrl D and ctrl C.
 		line_buffer = readline("minishell: ");
 		if (ft_strnstr(line_buffer, "\n", ft_strlen(line_buffer)))
 			write(1, "minishell: ", 11);
 		if (!ft_strncmp(line_buffer, "exit", ft_strlen(line_buffer)))
 			break ;
 		parse(line_buffer);
			//////	This fills the list s_token --- This list is the equivalent of the Command Table //////    
					char *token;						
					char *type;							
					struct t_token *next;				
					struct t_token *prev;				
			 Also returns errors in case of bad cmd input

		execute();
			//////  This reads list s_token ////
					Tries to execute cmd path like in pipex
					If not successfull make ft_strcmp to the builtins and redirects to function
					Returns 0 if successful and 1 if not successful
		
		free();
			////// This fills the list t_token and anything else //////

		free(line_buffer);
 	}
 	free(line_buffer);
}
*/