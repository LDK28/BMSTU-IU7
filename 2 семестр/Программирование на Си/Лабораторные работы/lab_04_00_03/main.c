#include "myfunctions.h"

int main(void)
{
	char str_in[NMAX] = "";
	if (fgets(str_in, NMAX, stdin) == NULL)
		return EXIT_FAILURE;

	if (*(str_in + strlen(str_in) - 1) != '\n')
		return LONG_STRING_ERROR;
	if (strlen(str_in) < 2)
		return EMPTY_STRING_ERROR;

	char words[NMAX/2][WMAX];
	size_t n = 0;
	if (make_words(str_in, words, &n))
		return EXIT_FAILURE;
	
	del_letters(words, &n);

	char new_str[NMAX] = "";
	for (size_t i = n - 2; i; --i)
		if (strcmp(*(words + i), *(words + n - 1)))
		{
			strcat(new_str, *(words + i));
			strcat(new_str, " ");
		}
	if (strcmp(*words, *(words + n - 1)))
	{
		strcat(new_str, *words);
		strcat(new_str, "\0");
	}
	else
		*(new_str + strlen(new_str) - 1) = 0;
	if (strlen(new_str) == 0)
		return SAME_WORDS_ERROR;
	printf("Result: %s\n", new_str);
	return EXIT_SUCCESS;
}