#include "myfunctions.h"


int main(void)
{
	char s1[NMAX];
	if (input(s1))
		return EXIT_FAILURE;
	
	char words1[NMAX/2 - 1][WMAX];
	size_t n1 = 0;
	if (make_words(s1, words1, &n1) != 0)
		return LONG_WORD_ERROR;

	char s2[NMAX];
	if (input(s2))
		return EXIT_FAILURE;

	char words2[NMAX/2 - 1][WMAX];
	size_t n2 = 0;
	if (make_words(s2, words2, &n2) != 0)
		return LONG_WORD_ERROR;
	
	puts("Result:");
	for (size_t i = 0; i < n1; ++i)
	{
		long check = 1;
		for (size_t j = 0; j < n2; ++j)
		{
			if (strcmp(*(words1 + i), *(words2 + j)) == 0)
			{
				printf("%s yes\n", *(words1 + i));
				check = 0;
				break;
			}
		}
		if (check)
			printf("%s no\n", *(words1 + i));
	}
	return EXIT_SUCCESS;
}