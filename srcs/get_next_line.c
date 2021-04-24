#include "cub3d.h"

static int		g_strlen(char *s)
{
	int size = 0;

	while (s[size])
		size++;
	return (size);
}

static char		*g_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;

	if (!(s = (char *)malloc(sizeof(char *) * (g_strlen(s1) + g_strlen(s2) + 1))))
		return (NULL);
	i = 0;	
	while (*s1)	
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = 0;
	return (s);
}

int				get_next_line(int fd, char **line)
{
	char	buf[2];
	char	*s;
	char	*temp;
	int 	i, ret;

	// set 0
	i = 0;
	while (i < 2)
		buf[i++] = 0;

	// read
	s = g_strjoin("", "");
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			break ;
		temp = g_strjoin(s, buf);
		free(s);
		s = temp;
	}
	*line = s;
	return (ret);
}
