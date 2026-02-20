#include "tools.h"
#include <stdlib.h> // malloc(), NULL
#include <string.h> // memcpy()


char *strjoin(const char *s1, const char *s2)
{
	size_t len1 = 0, len2 = 0;
	char   *res;

	if (!s1 || !s2)
		return (NULL);

	len1 = strlen(s1);
	len2 = strlen(s2);

	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);

	memcpy(res, s1, len1);
	memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';

	return (res);
}
