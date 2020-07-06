#include "waterdrop.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print(char *s)
{
	
	write(1, s, ft_strlen(s));
}

void	printr(char *s)
{
	print(MAG);
	print(s);
	print(RST);
}

void	help(void)
{
	printr("help\n");
}

char	*ft_strncpy(char *dst, char *src, size_t len)
{
	size_t i;

	i = 0;
	while (len)
	{
		if (!src[i])
		{
			while (len--)
				dst[i++] = '\0';
			break ;
		}
		dst[i] = src[i];
		i++;
		len--;
	}
	return (dst);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(char *s1)
{
	char	*r;
	size_t	sz;

	sz = ft_strlen(s1) + 1;
	if (!(r = malloc(sz)))
		return (0);
	return (ft_memcpy(r, s1, sz));
}

void	*ft_memset(void *b, int c, size_t len)
{
	void *beg;

	beg = b;
	while (len--)
	{
		*((char *)b) = (unsigned char)c;
		b++;
	}
	return (beg);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	s2len = ft_strlen(s2);
	s1len = ft_strlen(s1);
	if (!(s3 = (malloc(sizeof(char) * (s1len + s2len + 1)))))
		return (0);
	ft_strncpy(s3, s1, s1len);
	ft_strncpy(s3 + s1len, s2, s2len);
	s3[s1len + s2len] = '\0';
	return (s3);
}