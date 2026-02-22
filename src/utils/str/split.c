#include "utils/str.h"
#include <stdlib.h>


static size_t count_words(const char *s, char c)
{
	size_t count;
	int    in_word;

	count = 0;
	in_word = 0;
	while (*s) {
		if (*s != c && in_word == 0) {
			in_word = 1;
			count++;
		} else if (*s == c)
			in_word = 0;
		s++;
	}

	return (count);
}


static char *word_dup(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}


static void	free_all(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}


char **ft_split(const char *s, char c)
{
	char	**result;
	size_t	i;
	size_t	word_len;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = 0;
			while (s[word_len] && s[word_len] != c)
				word_len++;
			result[i] = word_dup(s, word_len);
			if (!result[i])
				return (free_all(result, i), NULL);
			i++;
			s += word_len;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
