#include "get_next_line_bonus.h"

int	found_newline(t_list	*stash)
{
	int		i;
	t_list	*current;

	current = ft_lstlast(stash);
	i = 0;
	if (stash == NULL)
		return (0);
	while (current->string[i])
	{
		if (current->string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current)
	{
		if (!current->next)
			return (current);
		current = current->next;
	}
	return (current);
}

void	generate_line(t_list	*stash, char	**list)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->string[i])
		{
			if (stash->string[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*list = malloc(sizeof(char) * (len + 1));
	if (*list == NULL)
		return ;
}

void	free_stash(t_list *stash)
{
	t_list	*temp;
	t_list	*current;

	current = stash;
	while (current)
	{
		free(current->string);
		temp = current->next;
		free(current);
		current = temp;
	}
}

int	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
