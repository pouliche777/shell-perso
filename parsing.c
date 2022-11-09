/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:30:19 by marvin            #+#    #+#             */
/*   Updated: 2022/11/08 18:30:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
	{	
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen((char *)s))
	{
		ptr = calloc(len + 1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	else
	   	ptr = calloc(len + 1, sizeof(char));
		if (ptr == NULL)
			return (NULL);
		ft_strlcpy(ptr, s + start, len + 1);
		return (ptr);
}


int	skip_quote(char *buffer, char c)
{
	int i;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)	
			return (i);
		i++;
	}
	printf("Invalid command\n");
	return (0);
}
int	count_cmds(char *buffer)
{
	int	i;

	i = 0;
	int 	nb_cmds = 1;
	while (buffer[i])
	{
		if (buffer[i] == '\'')
			i = i +1+ skip_quote(&buffer[i + 1] , '\'');
		else if (buffer[i] == '\"')
			i = i + 1+ skip_quote(&buffer[i + 1], '\"');
		else if (buffer[i] == '|')
			nb_cmds++;
		i++;
	}
	return (nb_cmds);
}
char ***parser(char *buffer, int nb_cmds)
{
	
	int	i;
	int j;
	int h;
	char ***cmds;
	i = 0;
	j = 0;
	h = 0;
	int k = 0;

	cmds = malloc(sizeof(char**) * nb_cmds);
	cmds[j] = malloc(sizeof(char *) * 100);

	while (nb_cmds > 0)
	{
		if (buffer[i] == 39)
		{
			i = i + skip_quote(buffer + (1 + i), 39);
			k++;
			i++;
			cmds[j][h] = ft_substr(buffer, k, (i-k));
			h++;
			k = i + 1;
			if (buffer[i])
				while (buffer[i]== ' ')
					i++;
		}
		else if (buffer[i] == '\"')
		{
			printf("voici la valeur de i :%d\n",i);
			i = i + skip_quote(buffer + 1 + i, '\"');
			k++;
			i++;
			printf("voici la valeur de i :%d\n",i);
			printf("voici la valeur de k :%d\n",k);
			cmds[j][h] = ft_substr(buffer, (k), (i-k));
			h++;
			k = i + 1;
			if (buffer[i])
				while (buffer[i+1]== ' ')
				{
					i++;
				}
			
		}
		else if (buffer[i] == ' ' || buffer[i] == '|' || buffer[i]== '\0')
		{
			
			cmds[j][h] = ft_substr(buffer, k, (i-k));
			h++;
			if (buffer[i])
				while (buffer[i+1]== ' ')
					i++;

			k = i + 1;
		}
		// if (buffer[0] == '|')
		//{
		//	
		if (buffer[i] == '\0' || buffer[i] == '|' )
		{
				printf("voici la valeur de i quand on change de cmd :%d\n",i);
			nb_cmds--;
			j++;
			h=0;
			if (buffer[i])
				cmds[j] = malloc(sizeof(char *) * 100);
		}

		//	h = 0;
	//	}
		i++;
		
		//while (buffer[i]== ' ')
		//{
		//	buffer++;
		//}
	}
	return (cmds);
}

int main (void)
{
	int i = 0;
	int j = 0;
	char str[]= "ls \'-a-l\' |\"ls  -l\"";
	printf("%s\n", str);
	
	char ***cmds;
	i = count_cmds(str);
		printf("nb_cmds :%d\n",i);
	cmds = parser(str, i);
	printf("%s", cmds[0][1]);
}