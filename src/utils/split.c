#include "minishell.h"

void	split_quotes(t_split *sp, char c)
{
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	while (sp->s[sp->i] && sp->s[sp->i] != c)
		sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
}

static void	put_word(t_split *sp, int c)
{
	if (c == PIPE || c == REDIRECT_IN || c == REDIRECT_OUT)
	{
		sp->arr[sp->j] = malloc(sizeof(char) + 1);
		if (malloc_gone_wrong(sp->arr, sp->j))
			return ;
		sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	}
	else
	{
		sp->arr[sp->j] = malloc(ft_word_len(sp->s, sp->i) * sizeof(char) + 1);
		if (malloc_gone_wrong(sp->arr, sp->j))
			return ;
		while (sp->s[sp->i])
		{
			if (sp->s[sp->i] && sp->s[sp->i] == '\"')
				split_quotes(sp, '\"');
			if (sp->s[sp->i] && sp->s[sp->i] == '\'')
				split_quotes(sp, '\'');
			while (check_new_token(&sp->s[sp->i]) == 3
				&& sp->s[sp->i] != '\"' && sp->s[sp->i] != '\'')
				sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
			if (sp->s[sp->i]
				&& (check_new_token(&sp->s[sp->i]) == 2 || sp->s[sp->i] == ' '))
				break ;
		}
	}
}

static void	put_word_extra(t_split *sp, int c)
{
	if (c == REDIRECT_IN)
	{
		if (sp->s[sp->i + 1] == '<')
		{
			sp->arr[sp->j] = malloc(sizeof(char) + 2);
			if (malloc_gone_wrong(sp->arr, sp->j))
				return ;
			sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
			sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
		}
		else
			put_word(sp, REDIRECT_IN);
	}
	else if (c == REDIRECT_OUT)
	{
		if (sp->s[sp->i + 1] == '>')
		{
			sp->arr[sp->j] = malloc(sizeof(char) + 2);
			if (malloc_gone_wrong(sp->arr, sp->j))
				return ;
			sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
			sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
		}
		else
			put_word(sp, REDIRECT_OUT);
	}
}

void	split_words(t_split *sp)
{
	while (sp->s[sp->i])
	{
		while (sp->s[sp->i] && sp->s[sp->i] == ' ')
			sp->i++;
		if (sp->s[sp->i])
		{
			if (sp->s[sp->i] == '|')
				put_word(sp, PIPE);
			else if (sp->s[sp->i] == '<')
				put_word_extra(sp, REDIRECT_IN);
			else if (sp->s[sp->i] == '>')
				put_word_extra(sp, REDIRECT_OUT);
			else
				put_word(sp, 0);
			sp->arr[sp->j][sp->k] = '\0';
			sp->j++;
			sp->k = 0;
		}
	}
	sp->arr[sp->j] = 0;
}

char	**ft_split_adapted(char *s)
{
	int		n;
	t_split	sp;

	n = countwords(s, 0, 0);
	sp.i = 0;
	sp.j = 0;
	sp.k = 0;
	sp.s = s;
	sp.arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!sp.arr)
		return (NULL);
	split_words(&sp);
	if (!*(sp.arr))
		return (free(sp.arr), NULL);
	return (sp.arr);
}
