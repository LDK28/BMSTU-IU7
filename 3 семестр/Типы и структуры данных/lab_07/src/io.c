#include "inc/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "inc/graph.h"
#include "inc/utils.h"

extern char *filename_data_global;

static graph_t *graph_global = NULL;

int input_point_of_grapth(graph_t *graph, size_t *point) {
    printf("Введите номер вершины: ");
    int temp = 0;
    if (scanf("%d", &temp) != 1) return -1;
    if (temp < 1 || temp > graph->num) return -1;
    *point = temp - 1;
    return 0;
}

int create_wrapper() {
    if (graph_global) free_graph(graph_global);

    FILE *file = fopen(filename_data_global, "r");
    if (!file) return -1;

    graph_global = create_from_file(file);
    if (!graph_global) return -1;

    return 0;
}

int print_matrix(matrix_t *matrix) {
    printf("|     |");
    for (size_t i = 0; i < matrix->cols; i++) printf("%5zu|", i + 1);

    printf("\n|");

    for (size_t i = 0; i < matrix->cols + 1; i++) printf("-----|");
    printf("\n");

    for (size_t i = 0; i < matrix->rows; i++) {
        printf("|%5zu|", i + 1);

        for (size_t j = 0; j < matrix->cols; j++)
        printf("    %c|", matrix->data[i][j] ? '1' : ' ');

        printf("\n");
    }
    return 0;
}

int print_wrapper() {
    FILE *file = fopen("temp.txt", "w");

    export_dot(file, graph_global);

    fclose(file);

    system("dot -Tpng temp.txt -otemp.png");
    system("open temp.png &");

    return 0;
}
int find_wrapper() {
    size_t point = 0;
    if (input_point_of_grapth(graph_global, &point)) {
        clear_input();
        return -1;
    }

    FILE *file = fopen("temp.txt", "w");

    export_dot_reachability(file, graph_global, point);

    fclose(file);

    system("dot -Tpng temp.txt -otemp.png");

    clear_input();
    printf("Из вершины %zu не достижимы вершины: \n", point + 1);
    int num = 0;
    for (size_t i = 0; i < graph_global->num; i++)
        if (!graph_global->reachability->data[point][i]) {
        printf("- %zu \n", i + 1);
        num++;
        }
    if (!num) printf("Все вершины достижимы.\n\n");

    system("open temp.png");

    return 0;
}

int print_matrixs_wrapper()
{
    printf("Матрица смежности: \n");
    print_matrix(graph_global->adjacency_matrix);
    printf("\nМатрица достижимости: \n");
    print_matrix(graph_global->reachability);
    return 0;
}

void print_menu()
{
    static struct
    {
        char *name;
        int (*action)(void);
    } actions[] = {
        {.name = "Показать граф", .action = print_wrapper},
        {.name = "Напечатать матрицы смежности и достижимости",
        .action = print_matrixs_wrapper},
        {.name = "Найти все вершины, недостижимые из заданной вершины",
        .action = find_wrapper},

        {.name = NULL, .action = NULL},
    };

    if (create_wrapper()) {
        printf("Ошибка открытия файла\n");
        return;
    }
    while (1)
    {
        printf("Меню \n\n");

        size_t diff = 0;
        size_t act_count = 0;
        for (size_t i = 0; actions[i].name; i++) {
        if (actions[i].action)
        {
            printf("%3zu) %s\n", i + 1 - diff, actions[i].name);
        }
        else
        {
            diff++;
            printf("===== %s\n", actions[i].name);
        }
        act_count++;
        }

        printf("\n  0) Выход \n");

        printf("Введите номер команды: ");
        int action = 0;
        if (scanf("%d", &action) == 0 || action > act_count - diff || action < 0) {
        wait_and_clear();
        printf("Неправильный номер команды.");
        return print_menu();
        }

        wait_and_clear();
        if (!action) return exit_handler();

        size_t i = 0;
        for (size_t j = 0; j < action; i++)
        if (actions[i].action) j++;

        if (actions[i - 1].action())
        {
        wait_and_clear();
        printf("Произошла ошибка\n");
        }

        wait_and_clear();
    }
}
