/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 16:03:33 by amalkevy          #+#    #+#             */
/*   Updated: 2018/01/13 16:03:36 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10000
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

int		get_next_line(const int fd, char **line);
char	*ft_strnew(size_t size);
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstadd(t_list **alst, t_list *new);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
#endif
