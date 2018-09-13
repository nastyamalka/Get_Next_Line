/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:42:49 by amalkevy          #+#    #+#             */
/*   Updated: 2018/01/13 15:50:55 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list				*ft_check_fd(t_list *ostatok, int fd)
{
	t_list			*new_lst;

	new_lst = ostatok;
	while (new_lst != NULL)
	{
		if (new_lst->content_size == (size_t)fd)
			return (new_lst);
		new_lst = new_lst->next;
	}
	return (NULL);
}

void				ft_del_lst(t_list **start, t_list *goal)
{
	t_list			*tmp;
	t_list			*del;

	tmp = (*start);
	while (tmp->next)
		while (tmp->next && tmp->next->content_size != goal->content_size)
			tmp = tmp->next;
	if (tmp->next)
	{
		free(tmp->content);
		del = tmp->next;
		tmp->next = del->next;
		free(del);
	}
	else
	{
		free((*start)->content);
		(*start) = NULL;
	}
}

int					check_newline_inlst(t_list **ost, char **line, t_list *tmp)
{
	int				i;
	char			*str;
	char			*p;

	i = (int)(ft_strchr(tmp->content, '\n') - (char*)(tmp->content));
	if (ft_strchr(tmp->content, '\n') == NULL)
	{
		str = *line;
		*line = ft_strjoin(tmp->content, str);
		free(str);
		ft_del_lst(ost, tmp);
		return (1);
	}
	else
	{
		str = *line;
		p = ft_strsub(tmp->content, 0, i);
		*line = ft_strjoin(str, p);
		free(str);
		free(p);
		str = ft_strsub((tmp->content), i + 1, ft_strlen(tmp->content));
		free(tmp->content);
		tmp->content = str;
		return (0);
	}
}

int					check_n_inbuf(char *buf, t_list **lst, char **line, int fd)
{
	int				i;
	t_list			*new_lst;
	char			*p[2];

	i = (int)(ft_strchr(buf, '\n') - buf);
	if (ft_strchr(buf, '\n') == NULL)
	{
		p[0] = (*line);
		*line = ft_strjoin(p[0], buf);
		free(p[0]);
		return (1);
	}
	p[0] = *line;
	p[1] = ft_strsub(buf, 0, i);
	*line = ft_strjoin((*line), p[1]);
	free(p[0]);
	free(p[1]);
	p[0] = ft_strsub((buf), i + 1, ft_strlen(buf));
	new_lst = ft_lstnew(p[0], ft_strlen(buf));
	free(p[0]);
	new_lst->content_size = (size_t)fd;
	ft_lstadd(lst, new_lst);
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	int				rd;
	char			*buf;
	t_list			*tmp;
	static t_list	*ostatok = NULL;

	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	rd = 1;
	buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	*line = ft_strnew(0);
	if ((tmp = ft_check_fd(ostatok, fd)) != NULL)
		rd = check_newline_inlst(&ostatok, line, tmp);
	while (rd > 0)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[rd] = '\0';
		if (check_n_inbuf(buf, &ostatok, line, fd) == 0)
		{
			free(buf);
			return (1);
		}
	}
	free(buf);
	return (((**line) == '\0' && ostatok == NULL) ? 0 : 1);
}
