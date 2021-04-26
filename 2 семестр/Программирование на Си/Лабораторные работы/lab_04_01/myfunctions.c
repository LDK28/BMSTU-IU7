#include "myfunctions.h"

const char*my_strpbrk(const char *string1, const char *string2)
{
	while (*string1)
	{
		const char *t = string2;
		while (*t)
		{
			if (*(string1) == *(t))
			{
				return string1;
			}
			++t;
		}
		++string1;
	}
	return NULL;
}

size_t my_strspn(const char *string1, const char *string2)
{
	size_t len = 0;
	while (*string1)
	{
		const char *t = string2;
		long check = 0;
		while (*t)
		{
			if (*string1 == *t)
			{
				check = 1;
				break;
			}
			++t;
		}
		if (check == 1)
			++len;
		else
			break;
		++string1;
	}
	return len;
}

size_t my_strcspn(const char *string1, const char *string2)
{
	size_t len = 0;
	while (*string1)
	{
		const char *t = string2;
		while (*t)
		{
			if (*string1 == *t)
				return len;
			++t;
		}
		++len;
		++string1;
	}
	return len;
}

const char*my_strchr(const char *string, int symbol)
{
	while (*string)
	{
		if (*string == symbol)
			return string;
		++string;
	}
	if (*string == symbol)
		return string;
	return NULL;
}

const char*my_strrchr(const char *string, int symbol)
{
	long length = 0;
	while (*string)
	{
		++length;
		++string;
	}
	string -= length;
	while (length >= 0)
	{
		if ((*(string + length)) == symbol)
			return string + length;
		--length;
	}
	return NULL;
}

