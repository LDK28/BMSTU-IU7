#include "myfunctions.h"

long make_words(char *string, char words[][WMAX], size_t *array_len)
{
	const char symbols[] = { ' ', ',', ';', ':', '-', '.', '!', '?', '\n', '\0' };
	char *word = strtok(string, symbols);
	while (word)
	{
		if (strlen(word) > WMAX - 1)
				return LONG_WORD_ERROR;
		for (size_t i = 0; *(word + i); ++i)
		{
			*(*(words + *array_len) + i) = *(word + i);
			*(*(words + *array_len) + i + 1) = 0;
		}
		++(*array_len);
		word = strtok(NULL, symbols);
	}
	if (*array_len < 2)
		return NOT_ENOUGH_WORDS_ERROR;
	
	return EXIT_SUCCESS;
}

void del_letters(char words[][WMAX], size_t *array_len)
{
	for (size_t i = 0; i < *array_len; ++i)
		for (size_t j = 1; *(*(words + i) + j); ++j)
			if (*(*(words + i) + j) == **(words + i))
			{
				for (size_t k = j; *(*(words + i) + k); ++k)
					*(*(words + i) + k) = *(*(words + i) + k + 1);
				--j;
			}	
}