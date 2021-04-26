#define __USE_MINGW_ANSI_STDIO 1
#include "myfunctions.h"
#include <string.h>

int main(void)
{
	// strpbrk
	char s1[256] = "mama";
	char s2[256] = "papa";
	if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	char s3[256] = "gang";
	char s4[256] = "wewe";
	if (strpbrk(s3, s4) != my_strpbrk(s3, s4))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	
	// strspn
	char s5[256] = "qwer11ty";
	char s6[256] = "ytrewq";	
	if (strspn(s5, s6) != my_strspn(s5, s6))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	if (strspn(s3, s4) != my_strspn(s3, s4))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}

	// strcspn	
	if (strcspn(s5, s6) != my_strcspn(s5, s6))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	if (strcspn(s3, s4) != my_strcspn(s3, s4))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}

	// strchr	
	if (strchr(s5, '1') != my_strchr(s5, '1'))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	if (strchr(s3, 'q') != my_strchr(s3, 'q'))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	if (strchr(s3, 0) != my_strchr(s3, 0))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}

	// strrchr	
	if (strrchr(s5, 'q') != my_strrchr(s5, 'q'))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	if (strrchr(s3, 'q') != my_strrchr(s3, 'q'))
	{
		puts("ERROR");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}