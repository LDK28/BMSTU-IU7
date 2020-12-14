#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "struct.h"
#include "sort.h"
#include "input.h"

#define EXIT -10

int main(void)
{
    setbuf(stdout, NULL);
	student_table_t student_table = {NULL, 0, 0};
    key_table_t key_table = {NULL, 0};
	student_t student;
	
	char name[LEN_NAME];
	int n, choice = 1;
	
	while (choice)
	{
		printf("\nPlease select the menu item you are interested in.\n");
		printf("\n  MENU:\n"
			   "  1 - Read student's table from file\n"
			   "  2 - Write student's table to file\n"
			   "  3 - Add record to table\n"
			   "  4 - Remove record from table\n"
			   "  5 - Search by key\n"
			   "  6 - Print student's table\n"
			   "  7 - Make key table\n"
			   "  8 - Print key table\n"
			   "  9 - Print table in key order\n"
			   "  10 - Sort student's table\n"
			   "  11 - Sort key table\n"
			   "  12 - Measure sorting time\n"
			   "  13 - Print table from file\n"
			   "  14 - Clear student's table\n"
			   "  15 - Clear key table\n"
			   "  0 - Exit\n");
			   
	    fflush(stdin);
	    printf("\n  Choice: ");
		
	    if (scanf("%d", &choice) == 1)
		{
			if (!choice)
			{
				clear_table(&student_table);
				printf("Exit\n\n");
				
				return EXIT;
			}
			else if (choice == 1)
			{
				input_string("Input file name: ", name, LEN_NAME);
				FILE *f = fopen(name, "r");
				
				if (!f)
				{
					printf("File does not exist.\n\n");
					continue;
				}
				
				if (read_table_from_file(f, &student_table))
					printf("Loading error.\n\n");
				else
					printf("Loaded.\n\n");
				fclose(f);
			}
			else if (choice == 2)
			{
				input_string("Input file name: ", name, LEN_NAME);
				FILE *f = fopen(name, "w");
				
				write_table_to_file(f, &student_table);
				fclose(f);
				printf("Loaded.\n\n");
			}
			else if (choice == 3)
			{
				input_student(&student);
				add_to_table(&student_table, &student);
				printf("The record is added.\n\n");
			}
			else if (choice == 4)
			{
				input_number("Input student's index to delete", &n, 1, student_table.n);
				remove_from_table(&student_table, n);
				printf("Deleted.\n\n");
			}
			else if (choice == 5)
				search(&student_table);
			else if (choice == 6)
				output_table(&student_table);
			else if (choice == 7)
			{
				make_key_table(&student_table, &key_table);
				printf("Key table was created.\n\n");
			}
			else if (choice == 8)
				print_key_table(&key_table);
			else if (choice == 9)
				print_student_table_by_key(&student_table, &key_table);
			else if (choice == 10)
			{
				sort_student_table(&student_table);
				printf("Student's table was sorted.\n\n");
			}
			else if (choice == 11)
			{
				sort_key_table(&key_table);
				printf("Key table was sorted.\n\n");
			}
			else if (choice == 12)
                measure_sorting_time();
			else if (choice == 13)
			{
				input_string("Input file name: ", name, LEN_NAME);
				FILE *f = fopen(name, "r");
				
				if (!f)
				{
					printf("File does not exist.\n");
					continue;
				}
				
				print_table_from_file(f);
				fclose(f);
			}
            else if (choice == 14)
			{
				clear_table(&student_table);
				printf("Student's table was cleared.\n\n");
			}
			else if (choice == 15)
			{
				clear_key_table(&key_table);
				printf("Key table was cleared.\n\n");
			}
            else
                printf("Invalid input.\n");
		}
		else
			printf("Invalid input.\n");
	}
	return NO_ERR;
}

