/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:01:02 by vsergio           #+#    #+#             */
/*   Updated: 2022/06/01 15:17:34 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	//a funcao retorna 1 linha a cada vez que eh chamada, se eu passo
	//um buffer que detecta varias quebras de linha ('\n'), devo fazer
	//um loop na chamada da funcao para printar todas as quebras
	static	t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	//1. read from fd and add to the linked list (stash)
	read_and_stash(&stash, fd);
	//if my stash is equal to NULL, thats because is a empty file
	if (stash == NULL)
		return (NULL);
	//2. extract from the stash to line
	extract_line(stash, &line);
	//3. clean stash after put in line
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
// use read() to add characters in the stash
void	read_and_stash(t_list **stash, int fd)
{
	char	*buffer;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		readed = read(fd, buffer, BUFFER_SIZE);
		//if its in the end of file and haven't content to stash, free and return
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buffer);
			return ;
		}
		//needs to be readed instead of buffzer_size because if i put
		//a big buffzer_size like = 10000, and i read only 15 characters
		//i would allocating more than necessary
		buffer[readed] = '\0';
		add_to_stash(stash, buffer, readed);
		free(buffer);
	}
}
// add the content of our buffer to te end of our stash
void	add_to_stash(t_list **stash, char *buffer, int readed)
{
	int		i;
	t_list	*end_stash;
	t_list	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->string = malloc(sizeof(t_list) * (readed + 1));
	if (new_node->string == NULL)
		return ;
	new_node->next = NULL;
	while (buffer[i] && i < readed)
	{
		new_node->string[i] = buffer[i];
		i++;
	}
	new_node->string[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	end_stash = ft_lstlast(*stash);
	end_stash->next = new_node;
}
// extracts all characters from our stash and stores them in out line
//stopping after the first \n it encounters
void	extract_line(t_list *stash, char	**line)
{
	int i;
	int j;

	if (stash == NULL)
		return ;
	generate_line(stash, line);
	j = 0;
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		// se terminou a leitura da stash e nao encontrou o '\n'
		// ira resetar o indice e buscar na proxima stash o '\n'
		while (stash->string[i])
		{
			//caso encontre o \n, iremos apenas fazer o incremento dele no
			//final da linha e dar break no codigo, pois queremos apenas
			//imprimir 1 quebra de linha por linha
			if (stash->string[i] == '\n')
			{	
				(*line)[j++] = stash->string[i];
				break ;
			}
			//nao necessariamente o stash que estou verificando vai ter o \n
			//entao devo ter um indice apenas para o line, para ele n ser
			//resetado caso o stash n encontre o \n, e ai sim ele continuar
			// da onde parou a ultima vez pra ir incrementando ate encontrar
			//o \n no stash
			(*line)[j++] = stash->string[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}
//after extracting the line that was read, we dont need those characters 
//anymore, this function clears the stash so only the characters that have
//not been returned at the end of get_next_line() remain in our static stash
void	clean_stash(t_list **stash)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;
	int		j;

	j = 0;
	new_node = malloc(sizeof(t_list));
	if (stash == NULL || new_node == NULL)
		return ;
	last_node = ft_lstlast(*stash);
	i = 0;

	while (last_node->string[i] && last_node->string[i] != '\n')
		i++;
	if (last_node->string && last_node->string[i] == '\n')
		i++;

	new_node->string = malloc(sizeof(char) * ((ft_strlen(last_node->string) - i) + 1));
	//nesse no limpo, que ira conter apenas o conteudo apos a quebra de linha, devera ser setado o proximo
	//next dele para NULL, pra quando entrar no loop novamente em busca da proxima quebra, ele ter uma
	//referencia e saber para onde apontar, pois se for passado um buffer menor que o minimo pra encontrar
	//o '\n' no primeiro loop, ele ira ficar num loop ate encontrar o '\n', e caso encontre e o buffer sobre conteudo
	//apos a quebra de linha, esse novo buffer que resta precisa ter setado o proximo para NULL.
	new_node->next = NULL;
	if (new_node->string == NULL)
		return ;
	//apos fazer o malloc da ultima string do que restou apos a quebra '\n' 
	//agora ira pegar o restante a partir do indice 'i' que sobrou depois da quebra '\n' e incluir no novo node
	while (last_node->string[i])
		new_node->string[j++] = last_node->string[i++];
	new_node->string[j] = '\0';
	//tudo que vier antes da stash que foi encontrada a primeira ocorrencia
	// da '\n', podera ser limpo, restando apenas o que vem apos a '\n'
	//pois podera servir pra complementar o proximo print de linha
	free_stash(*stash);
	*stash = new_node;
	//quando a quebra de linha existir na stash, a stash estara no final
	//pois sempre que uma stash eh adicionada, ela vai pro final da matriz
	//entao, quando uma eh encontrada, ela sera a ultima
	
	//logo eu limpo essa stash que havia a '\n', mas eu nao limpo
	//o que vem anterior dela, pois ao chamar a funcao gnl novamente
	//preciso saber da onde terminei o retorno da funcao anterior
	//para dar segmento, atraves da static stash

	//ao chamar a funcao novamente, como ele pula o que ja foi printado?
	//atraves da funcao read? ja grava onde parou a ultima lida?
}
