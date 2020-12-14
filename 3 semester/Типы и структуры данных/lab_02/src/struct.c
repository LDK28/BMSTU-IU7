#include "struct.h"
#include "input.h"

// Чтение данных о студенте с клавиатуры в структуру, на которую указывает указатель student
void input_student(student_t *student)
{
	input_string("Input the student's name: ", student->name, LEN_NAME);
	input_string("Input the student's surname: ", student->surname, LEN_SURNAME);
	input_bool("Input the gender of the student (0 - female, 1 - male): ", &student->gender);
	input_number("Input the student's age: ", &student->age, 16, 45);
	input_number("Input the student's group: ", &student->group, 1, 7);
	input_number("Input the student's average grade: ", &student->average_grade, 2, 5);
	input_number("Input the student's year of admission: ", &student->admission_year, 2012, 2020);
	input_bool("Input the student's type of residence (0 - house, 1 - hostel): ", &student->house_type);
	
	if (!student->house_type)
	{
		input_string("Input the street: ", student->adress.home.street, LEN_STREET);
		input_number("Input the house number: ", &student->adress.home.house, 1, 120);
		input_number("Input the flat number: ", &student->adress.home.flat, 1, 120);
	}
	else 
	{
		input_number("Input the hostel number: ", &student->adress.hostel.hostel_num, 1, 10);
		input_number("Input the room number: ", &student->adress.hostel.room, 1, 60);
	}
}

// Вывод данных о студенте из структуры, на которую указывает указатель student
void output_student(student_t student)
{
    printf("Name:              %s\n", student.name);
	printf("Surname:           %s\n", student.surname);
    if (!student.gender)
        puts("Gender:            female");
    else
        puts("Gender:            male");
	printf("Age:               %d\n", student.age);
	printf("Group:             %d\n", student.group);
	printf("Average grade:     %d\n", student.average_grade);
	printf("Year of admission: %d\n", student.admission_year);
	printf("Type of residence: ");
	
    if (!student.house_type)
    {
        puts("house");
        printf("Street:            %s\n", student.adress.home.street);
		printf("House number:      %d\n", student.adress.home.house);
		printf("Flat number:       %d\n", student.adress.home.flat);
    }
    else 
	{
        puts("hostel");
		printf("Hostel number: %d\n", student.adress.hostel.hostel_num);
		printf("Room number: %d\n", student.adress.hostel.room);
	}
}

// Чтение данных о студенте из файла, на который указывает f, в структуру, на которую указывает указатель student
int read_student_from_file(FILE *f, student_t *student)
{	
	if (fscanf(f, "%[^\n]\n", student->name) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%[^\n]\n", student->surname) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%d\n", &student->gender) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%d\n", &student->age) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%d\n", &student->group) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%d\n", &student->average_grade) != 1)
        return INCORRECT_DATA_ERROR;
	if (fscanf(f, "%d\n", &student->admission_year) != 1)
        return INCORRECT_DATA_ERROR;
	
    if (fscanf(f, "%d\n", &student->house_type) != 1)
        return INCORRECT_DATA_ERROR;
	
    if (!student->house_type)
	{
		if (fscanf(f, "%[^\n]\n", student->adress.home.street) != 1)
            return INCORRECT_DATA_ERROR;
		if (fscanf(f, "%d\n", &student->adress.home.house) != 1)
            return INCORRECT_DATA_ERROR;
		if (fscanf(f, "%d\n", &student->adress.home.flat) != 1)
            return INCORRECT_DATA_ERROR;
    }
    else 
	{
		if (fscanf(f, "%d\n", &student->adress.hostel.hostel_num) != 1)
            return INCORRECT_DATA_ERROR;
		if (fscanf(f, "%d\n", &student->adress.hostel.room) != 1)
            return INCORRECT_DATA_ERROR;
	}
	return EXIT_SUCCESS;
}

// Вывод данных о студенте в файл, на который указывает f, из структуры, на которую указывает указатель student
void write_student_to_file(FILE *f, student_t student)
{
	fprintf(f, "\n");
	
	fprintf(f, "%s\n", student.name);
	fprintf(f, "%s\n", student.surname);
	fprintf(f, "%d\n", student.gender);
	fprintf(f, "%d\n", student.age);
	fprintf(f, "%d\n", student.group);
	fprintf(f, "%d\n", student.average_grade);
	fprintf(f, "%d\n", student.admission_year);
	
    fprintf(f, "%d\n", student.house_type);
	
    if (!student.house_type)
    {
		fprintf(f, "%s\n", student.adress.home.street);
		fprintf(f, "%d\n", student.adress.home.house);
		fprintf(f, "%d\n", student.adress.home.flat);
    }
    else 
	{
		fprintf(f, "%d\n", student.adress.hostel.hostel_num);
		fprintf(f, "%d\n", student.adress.hostel.room);
	}
}

// Очистка списка студентов, на который указывает table
void clear_table(student_table_t *table)
{
    table->n = 0;
    table->max_n = 0;

    if (table->pb)
    {
        free(table->pb);
        table->pb = NULL;
    }
}

// Добавление студента student в список table
int add_to_table(student_table_t *table, const student_t *student)
{

    if (table->n >= table->max_n)
    {
		student_t *p_t = table->pb;
        student_t *p_free = table->pb;

        table->max_n += STEP;

        student_t *p_new = malloc(table->max_n * sizeof(struct student));

        if (!p_new)
            return ERR_STRUCT;

        table->pb = p_new;

        for (int i = 0; i < table->n; i++)
        {
            *p_new = *p_t;
            p_t++;
            p_new++;
        }
        free(p_free);
    }
    table->pb[table->n++] = *student;

    return NO_ERR;
}

// Удаление студента под номером i из списка table
int remove_from_table(student_table_t *table, int i)
{
	if (i < 1 || i > table->n)
        return ERR_PARAM;

    table->pb[i-1] = table->pb[--table->n];
	
    return NO_ERR;
}

// Чтение списка студентов из файла f в table
int read_table_from_file(FILE *f, student_table_t *table)
{
    int n;

    if (!f)
        return ERR_READ;
	
    clear_table(table);

    if (fscanf(f, "%d\n\n", &n) != 1)
        return ERR_SIZE;

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "\n");
        student_t *student = malloc(sizeof(student_t));;
        if (read_student_from_file(f, student))
            return INCORRECT_DATA_ERROR;
        add_to_table(table, student);
    }

    fclose(f);
    return NO_ERR;
}

// Запись списка студентов table в файл f
void write_table_to_file(FILE *f, student_table_t *table)
{
    student_t *pcur = table->pb;
	
    fprintf(f, "%d\n\n", table->n);
	
    for (int i = 0; i < table->n; i++)
    {
		write_student_to_file(f, *pcur);
        pcur++;
    }
}

// Вывод списка студентов table на экран
void output_table(student_table_t *table)
{
    student_t *pcur = table->pb;
	
    if (!table->n)
        printf("The table is incorrect!\n\n");
    else
    {
		printf("\nTable:\n");
        printf("------------------------------------------------------\n");
		
        for (int i = 0; i < table->n; i++)
        {
            printf("[Student №%d]\n\n", (i + 1));
            output_student(*pcur);
            printf("------------------------------------------------------\n");
			
            pcur++;
        }
    }
}

//  Очистка списка ключей keys
void clear_key_table(key_table_t *keys)
{
	keys->n = 0;
	
    if (keys->pb)
    {
        free(keys->pb);
        keys->pb = NULL;
    }
}

// Создание списка ключей keys из списка студентов table
int make_key_table(student_table_t *table, key_table_t *keys)
{
    student_t *student;
    struct key *key;

    clear_key_table(keys);

    keys->n = table->n;
    keys->pb = malloc(sizeof(struct key) * keys->n);
	
    if (!keys->pb)
        return ERR_STRUCT;
	
    student = table->pb;
    key = keys->pb;
	
    for (int i = 0; i < keys->n; i++)
    {
        key->id = i;
        key->key = student->age;
        key++;
        student++;
    }

    return NO_ERR;
}

// Вывод списка ключей keys на экран
void print_key_table(const key_table_t *keys)
{
    if (!keys->n)
        printf("Key table is empty.\n\n");
    else
    {
		printf("\nKey table:\n\n");
        struct key *pcur = keys->pb;
        printf("----------------------------\n");
		printf("    |   Student's age\n");
		printf("----------------------------\n");
		
        for (int i = 0; i < keys->n; i++)
        {
            printf("Id №|   %d\n", pcur->id + 1);
            printf("Key |   %d\n", pcur->key);
            printf("----------------------------\n");
			
            pcur++;
        }
    }
}

// Вывод списка студентов table по ключам keys
int print_student_table_by_key(const student_table_t *table, const key_table_t *keys)
{
    struct key *key = keys->pb;

    if (keys->n != table->n)
    {
        printf("Different sizes of tables.\n\n");
        return ERR_SIZE;
    }
	
    if (!table->n)
	{
        printf("Table is empty.\n\n");
		return ERR_SIZE;
	}
	
    else
    {
		printf("\nTable in key order:\n");
        printf("------------------------------------------------------\n");
        for (int i = 0; i < keys->n; i++)
        {
            if (key->id < 0 || key->id > (table->n - 1))
                return ERR_ID;
			
            printf("[Student №%d]\n\n", (i + 1));
            output_student(table->pb[key->id]);
            printf("------------------------------------------------------\n");
			
            key++;
        }
    }
	
    return NO_ERR;
}

void search(student_table_t *table)
{
    int flag = 0;
	int year;
	student_t *student = table->pb;
	
	input_number("Input the needed year of admission to find it(Students living in hostel)", &year, 2012, 2020);

    for (int i = 0; i < table->n; i++)
    {
        if (student->house_type && year == student->admission_year)
        {
            flag++;
            printf("[Student №%d]\n\n", (i + 1));
			output_student(*student);
            printf("------------------------------------------------------\n");
        }
        student++;
    }

    if (!flag)
        printf("Nothing found.\n\n");
}

// Вывод списка студентов из файла f
void print_table_from_file(FILE *f)
{
	student_table_t student_table = {NULL, 0, 0};
	read_table_from_file(f, &student_table);
	output_table(&student_table);
}

