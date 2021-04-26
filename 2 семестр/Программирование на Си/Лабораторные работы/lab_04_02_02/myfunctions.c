#include "myfunctions.h"

long input(char *string)
{
	long symb;
	size_t pos = 0;
	do
	{
		symb = getchar();
		if (pos > NMAX - 1)
			return LONG_STRING_ERROR;
		*(string + pos) = symb;
		++pos;
	}
	while ((symb != '\n') && (symb != EOF));
	if (pos == 1)
		return EMPTY_STRING_ERROR;
	*(string + pos) = 0;
	return EXIT_SUCCESS;
}

long make_words(const char *string, char words[][WMAX], size_t *array_len)
{
	char symbols[] = { ' ', ',', ';', ':', '-', '.', '!', '?', '\n', '\0' };
	char word[WMAX];
	size_t word_len = 0;
	while (*string)
	{
		long check_let = 1, check_symb = 0;
		for (size_t j = 0; *(symbols + j); ++j)
		{
			if (*string == *(symbols + j))
			{
				check_let = 0;
				break;
			}
			if (*(string + 1) == *(symbols + j))
				check_symb = 1;
		}
		if (check_let == 1)
		{
			*(word + word_len) = *string;
			++word_len;
			if (word_len > WMAX - 1)
				return LONG_WORD_ERROR;
			if (check_symb == 1)
			{
				*(word + word_len) = 0;
				long check = 1;
				for (size_t i = 0; i < *array_len; ++i)
				{
					if (strcmp(word, *(words + i)) == 0)
					{
						check = 0;
						break;
					}
				}
				if (check == 1)
				{
					for (size_t i = 0; i < word_len + 1; ++i)
						*(*(words + *array_len) + i) = *(word + i);
					++(*array_len);
				}
				word_len = 0;
			}
		}
		++string;
	}
	return EXIT_SUCCESS;
}