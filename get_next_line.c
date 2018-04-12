/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:54:40 by acouturi          #+#    #+#             */
/*   Updated: 2017/11/29 13:54:34 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static t_file	*crea_liste(const int fd, t_file *firstlst)
{
	t_file		*liste;
	t_file		*tmp;

	if (!(liste = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	liste->memstr = NULL;
	liste->start = NULL;
	liste->next = NULL;
	liste->fd = fd;
	tmp = firstlst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = liste;
	}
	return (liste);
}

static t_file	*crea_chaine(const int fd)
{
	t_file			*liste;
	static t_file	*firstlst = NULL;

	liste = firstlst;
	while (liste)
	{
		if (liste->fd == fd)
			break ;
		liste = liste->next;
	}
	if (!liste)
	{
		if (!(liste = crea_liste(fd, firstlst)))
			return (NULL);
	}
	if (!firstlst)
		firstlst = liste;
	if (!liste->memstr)
	{
		if (!(liste->memstr = ft_strdup("")))
			return (NULL);
		liste->start = liste->memstr;
	}
	return (liste);
}

static int		returnline(char *mem, char **line, t_file *liste)
{
	if (mem)
		*mem++ = 0;
	else
		mem = NULL;
	if (!(*line = ft_strdup(liste->memstr)))
		return (-1);
	liste->memstr = mem;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*mem;
	int				charlu;
	char			buffer[BUFF_SIZE + 1];
	t_file			*liste;

	if (fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0))
		return (-1);
	ft_bzero(buffer, BUFF_SIZE + 1);
	if (!(liste = crea_chaine(fd)))
		return (-1);
	while (!(mem = ft_strchr(liste->memstr, '\n')))
	{
		charlu = read(liste->fd, buffer, BUFF_SIZE);
		if (charlu == 0 && ft_strcmp(liste->memstr, ""))
			break ;
		if (charlu == 0)
			return (0);
		if (!(liste->memstr = ft_strjoin(liste->memstr, buffer)))
			return (-1);
		if (liste->start)
			free(liste->start);
		liste->start = liste->memstr;
		ft_bzero(buffer, BUFF_SIZE);
	}
	return (returnline(mem, line, liste));
}
