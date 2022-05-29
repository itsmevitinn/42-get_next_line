#include "get_next_line.h"
//looks for a newline in the given linked listg

int	found_new_line(t_list	*stash)
{
	int i;
	t_list	*current;

	current = ft_lstlast(stash);
	i = 0;
	if (stash == NULL)
		return (0);
	while (current->string[i] != '\0')
	{
		if(current->string[i] == '\n')
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
		if(!current->next)
			return (current);
		current = current->next;	
	}
	return (current);
}

void	generate_line(t_list	*stash, char	**list)
{
	int i;
	int len;

	i = 0;
	while (stash)
	{
		len = 0;
		while (stash->string[i])
		{
			if(stash->string[i] == '\n')
			{
				len++;
				break;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*list = malloc(sizeof(char) * (len + 1));
	if (*list == NULL)
		return; 
}

void	free_stash(t_list *stash)
{
	t_list	*temp;
	t_list	*current;

	current = stash;
	while(current)
	{
		free(current->string);
		temp = current->next;
		free(current);
		current = temp;
	}
}

int	ft_strlen(const char	*str)
{
	int i;
	int	len;
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}
