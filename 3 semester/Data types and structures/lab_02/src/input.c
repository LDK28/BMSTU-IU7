#include "input.h"

// Обработка вводимых пользователем символов в число number после вывода сообщения message до корректного ввода
void input_number(char *message, int *number, int beg, int end)
{
    *number = end + 1;
    printf("%s (in range (%d; %d)):\n", message, beg, end);
    while (scanf("%d", number) == 0 || !(*number >= beg && *number <= end))
    {
        printf("Wrong input! Please, try again: ");
	    fflush(stdin);
    }
    puts("\n");
}

// Обработка вводимых пользователем символов(0 или 1), после вывода сообщения message до корректного ввода
void input_bool(char *message, int *number)
{
    *number = -1;
    puts(message);
    while (scanf("%d", number) != 1 || !(*number == 0 || *number == 1))
	{
        printf("Wrong input! Please, try again: ");
	    fflush(stdin);
    }
    puts("\n");
}

// Обработка вводимых пользователем символов в строку string, максимальной длины max_len, после вывода сообщения message
void input_string(char *message, char *string, int max_len)
{
    char c;
    int end = 0;
    int i = -1;

    fflush(stdin);
    while (1)
    {
        puts(message);
        printf("(Max %d characters)\n\n", max_len - 1);

        for (i = 0; i < max_len; i++)
        {
            if (scanf("%c", &c) == 1)
            {
                if (c != '\n')
                    *(string + i) = c;
                else
                {
                    *(string + i) = 0;
                    end = 1;
                    break;
                }
            }
            else
            {
                *(string + i) = 0;
                end = 1;
                break;
            }
        }
		fflush(stdin);
        if (!end)
            printf("Too much characters. Try again.\n");
        else if (!string[0])
        {
            printf("Wrong input! Please, try again:\n");
            end = 0;
        }
        else
        {
            puts("\n");
            return;
		}
    }
}

